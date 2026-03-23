# 🧬 BioinfoParser-CPP

A high-performance tool for processing and analyzing genomic sequences (FASTA).

BioinfoParser-CPP is a Command Line Interface (CLI) application developed in **C++23**, designed to handle FASTA files with a focus on memory efficiency and analytical precision. The tool processes large volumes of genomic data, extracting vital statistics and performing molecular transformations safely through a robust exception-handling system.

## 🚀 Key Features

- **Multi-FASTA Parsing**: Robust reading of files containing multiple sequences and metadata.
- **Composition Analysis**:
  - Automatic calculation of **GC Content** (Guanine and Cytosine).
  - Total sequence length metrics (bp).
- **Molecular Transformations**:
  - Sequence normalization (automatic conversion of lowercase characters).
  - Generation of new processed FASTA files following industry standards.
- **Dual-Stream Output**:
  - `.processed.fasta`: File containing validated and formatted sequences.
  - `.stats.txt`: Human-readable technical report with quality and composition metrics.

## 🛠️ Technical Highlights

This project was built applying **Clean Code** principles and the latest language features:

- **Modern C++ (C++23)**: Leverages `std::format` and `std::optional` for cleaner, safer, and more efficient code.
- **OOD Architecture**: Clear separation of concerns between `FastaParser`, `BioSequence`, and `ReportGenerator` classes.
- **Robustness**: Validation system that identifies issues in corrupted or missing files without interrupting the system flow.
- **Cross-Platform**: Guaranteed support for Windows (MSVC), Linux, and macOS via CMake.

## ⚙️ Build and Installation

The project uses **CMake** (version 3.25 or higher) to manage the build process:

```bash
# 1. Create build directory
mkdir build && cd build

# 2. Configure the project
cmake ..

# 3. Build
cmake --build . --config Debug

💻 Usage

The command-line interface is intuitive and designed for seamless integration into automation pipelines.

Execution Example (Windows)

./Debug/bio_parser.exe --input raw_data.fasta --output processed_genome

Execution Example (Unix/macOS)

./bio_parser --input raw_data.fasta --output processed_genome

Available Flags:

    --input <file> : Path to the source .fasta file.

    --output <name> : Base name for output files (generates <name>.processed.fasta and <name>.stats.txt).

📂 Repository Structure

├── src/            # Implementation (.cpp)
├── include/        # Headers and Definitions (.hpp)
├── data/           # Sample FASTA files for testing
├── build/          # Binaries and build files (locally generated)
├── run_tests.sh    # Cross-platform test automation script
├── LICENSE         # MIT License
└── README.md       # Project documentation

⚖️ License

This project is licensed under the MIT License.

Developed by Vitor Cavalcante IT Coordinator & Full Stack Developer with a hybrid background in Systems and Biology.
```
