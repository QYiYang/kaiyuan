import sqlite3   
import uuid   
import tkinter as tk   
from tkinter import messagebox, simpledialog   
from pyzbar.pyzbar import decode   
from PIL import Image, ImageTk

   
# 数据库连接与初始化   
def init_database():
    conn = sqlite3.connect('supermarket.db')
    cursor = conn.cursor()

    # 创建商品表
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS products (
            id TEXT PRIMARY KEY,
            name TEXT NOT NULL,
            price REAL NOT NULL,
            stock INTEGER NOT NULL
        )
    ''')

    # 创建用户表
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id TEXT PRIMARY KEY,
            username TEXT NOT NULL,
            password TEXT NOT NULL
        )
    ''')

    # 创建订单表
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS orders (
            id TEXT PRIMARY KEY,
            user_id TEXT NOT NULL,
            product_ids TEXT NOT NULL,
            total_price REAL NOT NULL,
            FOREIGN KEY (user_id) REFERENCES users (id)
        )
    ''')

    conn.commit()
    return conn

   
# 商品管理类   
class ProductManager:
    def __init__(self, conn):
        self.conn = conn

    def add_product(self, name, price, stock):
        product_id = str(uuid.uuid4())
        cursor = self.conn.cursor()
        cursor.execute('INSERT INTO products (id, name, price, stock) VALUES (?,?,?,?)',
                       (product_id, name, price, stock))
        self.conn.commit()
        return product_id

    def update_product_stock(self, product_id, new_stock):
        cursor = self.conn.cursor()
        cursor.execute('UPDATE products SET stock =? WHERE id =?', (new_stock, product_id))
        self.conn.commit()

    def get_product_by_id(self, product_id):
        cursor = self.conn.cursor()
        cursor.execute('SELECT * FROM products WHERE id =?', (product_id,))
        return cursor.fetchone()

   
# 用户管理类   
class UserManager:
    def __init__(self, conn):
        self.conn = conn

    def register_user(self, username, password):
        user_id = str(uuid.uuid4())
        cursor = self.conn.cursor()
        cursor.execute('INSERT INTO users (id, username, password) VALUES (?,?,?)',
                       (user_id, username, password))
        self.conn.commit()
        return user_id

    def authenticate_user(self, username, password):
        cursor = self.conn.cursor()
        cursor.execute('SELECT * FROM users WHERE username =? AND password =?', (username, password))
        return cursor.fetchone()

   
# 购物车类   
class ShoppingCart:
    def __init__(self):
        self.items = []

    def add_item(self, product):
        self.items.append(product)

    def calculate_total(self):
        total = 0
        for item in self.items:
            total += item[2]
        return total

   
# 自助售货系统主类   
class SelfServiceSupermarket:
    def __init__(self):
        self.conn = init_database()
        self.product_manager = ProductManager(self.conn)
        self.user_manager = UserManager(self.conn)
        self.cart = ShoppingCart()

    def start_shopping(self):
        root = tk.Tk()
        root.title("自助小型超市售货系统")

        def login_or_register_gui():
            def login():
                username = username_entry.get()
                password = password_entry.get()
                user = self.user_manager.authenticate_user(username, password)
                if user:
                    messagebox.showinfo("登录成功", "登录成功！")
                else:
                    messagebox.showerror("登录失败", "用户名或密码错误。")

            def register():
                username = username_entry.get()
                password = password_entry.get()
                user_id = self.user_manager.register_user(username, password)
                messagebox.showinfo("注册成功", f"注册成功，您的用户ID为: {user_id}")

            login_register_window = tk.Toplevel(root)
            login_register_window.title("登录/注册")

            tk.Label(login_register_window, text="用户名:").grid(row=0, column=0)
            username_entry = tk.Entry(login_register_window)
            username_entry.grid(row=0, column=1)

            tk.Label(login_register_window, text="密码:").grid(row=1, column=0)
            password_entry = tk.Entry(login_register_window, show='*')
            password_entry.grid(row=1, column=1)

            login_button = tk.Button(login_register_window, text="登录", command=login)
            login_button.grid(row=2, column=0)

            register_button = tk.Button(login_register_window, text="注册", command=register)
            register_button.grid(row=2, column=1)

        def show_products_gui():
            products_window = tk.Toplevel(root)
            products_window.title("商品列表")

            cursor = self.conn.cursor()
            cursor.execute('SELECT * FROM products')
            products = cursor.fetchall()

            for i, product in enumerate(products):
                tk.Label(products_window,
                         text=f"ID: {product[0]}, 名称: {product[1]}, 价格: {product[2]}, 库存: {product[3]}").grid(
                    row=i, column=0)

        def add_to_cart_gui():
            def scan_qr():
                # 打开摄像头或文件读取二维码（这里假设从文件读取示例二维码图片）
                img = Image.open('example_qr.png')
                decoded_objects = decode(img)
                if not decoded_objects:
                    messagebox.showwarning("二维码识别失败", "无法识别二维码，请重新尝试。")
                    return
                product_id = decoded_objects[0].data.decode('utf - 8')
                product = self.product_manager.get_product_by_id(product_id)
                if product:
                    if product[3] > 0:
                        self.cart.add_item(product)
                        self.product_manager.update_product_stock(product_id, product[3] - 1)
                        messagebox.showinfo("加入购物车", f"{product[1]} 已加入购物车。")
                    else:
                        messagebox.showwarning("库存不足", "该商品已无库存。")
                else:
                    messagebox.showwarning("商品不存在", "商品不存在。")

            add_cart_window = tk.Toplevel(root)
            add_cart_window.title("加入购物车")
            tk.Button(add_cart_window, text="输入商品ID",
                      command=lambda: add_to_cart_gui()).pack()
            tk.Button(add_cart_window, text="扫描二维码", command=scan_qr).pack()

        def checkout_gui():
            if not self.cart.items:
                messagebox.showwarning("购物车为空", "购物车为空，请先添加商品。")
                return

            total = self.cart.calculate_total()
            messagebox.showinfo("结账", f"您的购物车总价为: {total} 元。")

            user_id = simpledialog.askstring("结账", "请输入您的用户ID:")
            product_ids = ','.join([item[0] for item in self.cart.items])
            order_id = str(uuid.uuid4())
            cursor = self.conn.cursor()
            cursor.execute('INSERT INTO orders (id, user_id, product_ids, total_price) VALUES (?,?,?,?)',
                           (order_id, user_id, product_ids, total))
            self.conn.commit()

            self.cart.items = []
            messagebox.showinfo("结账成功", "结账成功，感谢您的购物！")

        def create_product_gui():
            def add_product():
                name = name_entry.get()
                try:
                    price = float(price_entry.get())
                    stock = int(stock_entry.get())
                    self.product_manager.add_product(name, price, stock)
                    messagebox.showinfo("创建商品", "商品创建成功！")
                    create_product_window.destroy()
                except ValueError:
                    messagebox.showerror("输入错误", "价格和库存必须为数字。")

            create_product_window = tk.Toplevel(root)
            create_product_window.title("创建商品")

            tk.Label(create_product_window, text="商品名称:").grid(row=0, column=0)
            name_entry = tk.Entry(create_product_window)
            name_entry.grid(row=0, column=1)

            tk.Label(create_product_window, text="价格:").grid(row=1, column=0)
            price_entry = tk.Entry(create_product_window)
            price_entry.grid(row=1, column=1)

            tk.Label(create_product_window, text="库存:").grid(row=2, column=0)
            stock_entry = tk.Entry(create_product_window)
            stock_entry.grid(row=2, column=1)

            add_product_button = tk.Button(create_product_window, text="添加商品", command=add_product)
            add_product_button.grid(row=3, column=0)

        tk.Button(root, text="登录/注册", command=login_or_register_gui).pack()
        tk.Button(root, text="商品列表", command=show_products_gui).pack()
        tk.Button(root, text="加入购物车", command=add_to_cart_gui).pack()
        tk.Button(root, text="结账", command=checkout_gui).pack()
        tk.Button(root, text="创建商品", command=create_product_gui).pack()

        root.mainloop()

   
if __name__ == "__main__":
    supermarket = SelfServiceSupermarket()
    supermarket.start_shopping()


