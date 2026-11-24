import os

from cs50 import SQL

from datetime import datetime

from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd


# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    logged_user = session["user_id"]
    # [{'symbol': 'aapl', 'sum_quantity': 33}, {'symbol': 'dell', 'sum_quantity': 1}]
    quantity = db.execute(
        "SELECT symbol, SUM(quantity) AS sum_quantity FROM stocks WHERE owner = ? GROUP BY symbol", logged_user)

    quantity_list = []
    price_list = []
    shares_value_list = []

    for i, item in enumerate(quantity):
        # item["sum_quantity"]
        quantity_list.append(item["sum_quantity"])  # [33, 1]

        price = lookup(item["symbol"])
        price_list.append(price["price"])  # [335.31, 544.47]

        shares_value = quantity_list[i] * price_list[i]
        shares_value_list.append(shares_value)  # shares_value_list=[11054.01, 548.63]

    cash = db.execute("SELECT cash AS extracted_cash FROM users WHERE id = ?", logged_user)
    cash = cash[0]["extracted_cash"]
    cash = float(cash)

    portfolio = []
    for i, item in enumerate(quantity):
        new_dict = {
            "symbol": item["symbol"],
            "quantity": quantity_list[i],
            "price": (price_list[i]),
            "shares_value": (shares_value_list[i])
        }
        portfolio.append(new_dict)
    # [{'symbol': 'aapl', 'quantity': 33, 'price': '$336.61', 'shares_value': '$11,108.13'}, {'symbol': 'dell', 'quantity': 1, 'price': '$546.82', 'shares_value': '$546.82'}]
    print(portfolio)

    total_value = 0
    for i in portfolio:
        total_value += float(i["shares_value"])
    total_value += cash

    # render the page
    return render_template("index.html", index=portfolio, cash=cash, total_value=total_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        # show form to buy stock -> ask for symbol and number of shares, check for valid input (negative number, symbol is valid)
        return render_template("buy.html")

    else:
        # method=="POST"
        type = "buy"
        symbol = request.form.get("symbol")
        quoted = lookup(symbol)
        print(quoted)
        if quoted == None:
            return apology("Entered wrong symbol")

        if not request.form.get("symbol"):
            return apology("Symbol missing")

        shares = request.form.get("shares")
        if not shares.isdigit():
            return apology("Can't buy fractions of shares")
        shares = int(shares)

        if not request.form.get("shares"):
            return apology("Quantity missing")

        if shares < 1:
            return apology("Quantity must be > 1")

        price = quoted["price"]
        total = shares * price
        logged_user = session["user_id"]

        user_cash = (db.execute("SELECT cash FROM users WHERE id = ?", logged_user))
        user_cash = user_cash[0]["cash"]

        if total > user_cash:
            return apology("Not enough cash")

        date = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        # run sql statement to buy
        db.execute("INSERT INTO transactions (type, symbol, date, quantity, price, owner) VALUES (?, ?, ?, ?, ?, ?)",
                   type, symbol, date, shares, price, logged_user)

        # add shares to user portfolio
        db.execute("INSERT INTO stocks (owner, symbol, price, quantity, date) VALUES (?, ?, ?, ?, ?)",
                   logged_user, symbol, price, shares, date)

        # after successful buy operation, update cash value
        user_cash = user_cash - total
        db.execute("UPDATE users SET cash = ? WHERE id = ?", user_cash, logged_user)

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # show all buys and sells
    logged_user = session["user_id"]
    transactions = db.execute("SELECT * FROM transactions WHERE owner = ?", logged_user)
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        # method == "POST"
        symbol = request.form.get("symbol")
        if not request.form.get("symbol"):
            return apology("must enter symbol")

        quoted = lookup(symbol)
        if quoted == None:
            return apology("entered wrong symbol")
        else:
            return render_template("quoted.html", name=quoted["name"], price=quoted["price"], symbol=quoted["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "GET":
        # display registration form
        return render_template("register.html")

    else:
        # request method is POST, check for errors and insert new user into users table
        username = request.form.get("username")
        if not request.form.get("username"):
            return apology("must enter username")

        elif not request.form.get("password"):
            return apology("must enter password")

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords don't match")

        hashed_password = generate_password_hash(request.form.get("password"))

        try:
            db.execute("INSERT INTO users (username, hash, cash) VALUES (?, ?, ?)",
                       username, hashed_password, 10000)
        except ValueError:
            return apology("duplicate username")

    user_id = db.execute("SELECT id FROM users WHERE username = ?", request.form.get("username"))
    session["user_id"] = user_id[0]["id"]
    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    type = "sell"
    if request.method == "GET":
        # show form to sell stock -> ask for symbol and number of shares, check for valid input (negative number, symbol is valid)
        logged_user = session["user_id"]
        stocks = db.execute("SELECT symbol FROM stocks WHERE owner = ? GROUP BY symbol HAVING SUM(quantity) > 0", logged_user)
        return render_template("sell.html", stocks=stocks)

    else:
        # method=="POST"
        logged_user = session["user_id"]
        symbol = request.form.get("symbol")
        quoted = lookup(symbol)
        print(quoted)
        if quoted == None:
            return apology("Entered wrong symbol")

        if not request.form.get("symbol"):
            return apology("Symbol missing")

        shares_to_sell = request.form.get("shares")

        if not shares_to_sell.isdigit():
            return apology("Can't sell fractions of shares")

        shares_to_sell = int(shares_to_sell)

        if not request.form.get("shares"):
            return apology("Quantity missing")

        quantity = db.execute(
            "SELECT symbol, SUM(quantity) AS sum_quantity FROM stocks WHERE symbol = ? AND owner = ? GROUP BY symbol", symbol, logged_user)
        owned_shares = quantity[0]["sum_quantity"]

        if owned_shares < 1:
            return apology("Quantity must be > 1")

        price = quoted["price"]

        user_cash = (db.execute("SELECT cash FROM users WHERE id = ?", logged_user))
        user_cash = user_cash[0]["cash"]

        if shares_to_sell > owned_shares:
            return apology("Not enough shares to sell")

        date = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        # multiply by -1 in order to add a negative number of shares to sell
        shares_to_sell = shares_to_sell * -1

        # subtract shares from user portfolio
        db.execute("INSERT INTO stocks (owner, symbol, price, quantity, date) VALUES (?, ?, ?, ?, ?)",
                   logged_user, symbol, price, shares_to_sell, date)

        # run sql statement to sell
        db.execute("INSERT INTO transactions (type, symbol, date, quantity, price, owner) VALUES (?, ?, ?, ?, ?, ?)",
                   type, symbol, date, shares_to_sell, price, logged_user)

        # after successful buy operation, update cash value
        total = shares_to_sell * price * -1
        user_cash = user_cash + total
        db.execute("UPDATE users SET cash = ? WHERE id = ?", user_cash, logged_user)

        return redirect("/")


@app.route("/add", methods=["GET", "POST"])
def add():
    """Add funds"""
    if request.method == "GET":
        return render_template("add.html")

    else:
        # method "POST"
        logged_user = session["user_id"]
        cash = (db.execute("SELECT cash FROM users WHERE id = ?", logged_user))
        cash = cash[0]["cash"]

        funds_added = request.form.get("add")
        if not request.form.get("add"):
            return apology("must enter value")
        funds_added = int(funds_added)
        if funds_added < 1:
            return apology("Quantity must be > 1")

        cash += funds_added
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, logged_user)

    return redirect("/")
