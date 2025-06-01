# 🧭 Findy – A Fast and Friendly Desktop Search Engine

Findy is a lightweight, blazing-fast desktop search engine built with **C++**, **Qt**, **CLucene**, and **libmagic**. It provides instant search results across files and directories on your computer, indexing content smartly and efficiently — just like Google Desktop Search used to, but open source and modern.

---

## 🚀 Features

- 🔍 **Full-Text Search** using **CLucene**
- 🧠 **Magic File Type Detection** with `libmagic` (Unix `file` command logic)
- ⚡ **Fast Incremental Indexing**
- 🖼️ **Intuitive Qt GUI**
- 🔄 **Real-Time File Monitoring** (optional)
- 🧩 **Extensible & Modular Codebase**

---

## 📷 Screenshot

> _[Add a screenshot here of the UI in action if available]_  
> ![Findy Screenshot](resources/screenshot/findy.png)

---

## 🛠️ Built With

| Tech          | Purpose                             |
|---------------|-------------------------------------|
| **C++98**     | Core engine and indexing logic      |
| **Qt 4**      | GUI framework                      |
| **CLucene**   | Full-text search engine             |
| **libmagic**  | Detect file types via magic numbers |

---

## 📦 Installation

### 🔧 Prerequisites

- Qt 4
- C++11-compatible compiler (GCC, Clang, MSVC)
- CLucene development libraries
- libmagic (e.g. `libmagic-dev` on Debian)

### 🏗️ Build Instructions

```bash
# Clone the repository
git clone https://github.com/rnapoles/findy.git
cd findy

# Create build directory
mkdir build && cd build

# Run CMake
cmake ..

# Build the project
make -j$(nproc)

# Run the application
./findy
```

---

## 🎯 Usage

- Launch the app.
- Select directories to index.
- Begin typing in the search bar.
- Double-click results to open files.

You can also configure indexing behavior (e.g., file types to include) from the **Settings** menu.

---

## 🧩 Roadmap

- [x] Basic search UI
- [x] CLucene full-text integration
- [x] File type detection with libmagic
- [ ] Cross-platform installer (Windows, Linux, macOS)
- [ ] Systray integration
- [ ] Dark mode support
- [ ] Qt 5 support
- [ ] Qt 6 support

---

## 🙋‍♂️ Contributing

Pull requests are welcome! Please fork the repository and submit a PR with a meaningful description. Check out `CONTRIBUTING.md` (to be added) for code style and guidelines.

---

## 📄 License

GPL V3 License. See [LICENSE](LICENSE) for details.

---

## 🤝 Acknowledgments

- [CLucene](https://clucene.sourceforge.net/) – C++ port of Lucene
- [libmagic](https://darwinsys.com/file/) – File content-based type detection
- Qt Project – GUI framework

---

## 🧠 Author

Made with ❤️ by [rnapoles](https://github.com/rnapoles)