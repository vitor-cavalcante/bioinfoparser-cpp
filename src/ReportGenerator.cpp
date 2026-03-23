/*
 * Project: BioInfoParser-CPP
 * Author: Vitor Cavalcante
 * License: MIT
 */

#include "ReportGenerator.hpp"
#include <format> // C++20: Reliable formatting for MSVC
#include <iostream>
#include <string>

namespace BioInfoParser
{

    /**
     * Constructor: Opens the output file streams.
     * Appends specific extensions to the base filename provided by the user.
     */
    ReportGenerator::ReportGenerator(const std::string &base_filename)
    {
        fasta_out.open(base_filename + ".processed.fasta");
        stats_out.open(base_filename + ".stats.txt");

        if (!fasta_out || !stats_out)
        {
            std::cerr << "Error: Could not create output report files.\n";
        }
        else
        {
            // Automatically write the header when the generator is initialized
            write_header();
        }
    }

    /**
     * Destructor: Safely closes all active file streams.
     */
    ReportGenerator::~ReportGenerator()
    {
        if (fasta_out.is_open())
            fasta_out.close();
        if (stats_out.is_open())
            stats_out.close();
    }

    /**
     * Writes the sequence in biological FASTA format.
     * Adds a '_processed' suffix to the identifier for clarity.
     */
    void ReportGenerator::write_to_fasta(const BioSequence &seq)
    {
        if (!fasta_out.is_open())
            return;

        // Using std::format with streams to avoid C7595 immediate function errors
        fasta_out << std::format(">{}_processed\n{}\n",
                                 seq.get_identifier(),
                                 seq.get_sequence());
    }

    /**
     * Writes detailed sequence metrics to the statistics report.
     * Provides human-readable data including total length and GC percentage.
     */
    void ReportGenerator::write_to_stats(const BioSequence &seq)
    {
        if (!stats_out.is_open())
            return;

        // Fix: Using a temporary string for the separator to ensure it's a constant expression
        std::string line_separator(43, '-');

        stats_out << std::format("Sequence ID:   {}\n", seq.get_identifier());
        stats_out << std::format("Total Length:  {} bp\n", seq.get_length());
        stats_out << std::format("GC Content:    {:.2f}%\n", seq.get_gc_content());
        stats_out << std::format("{}\n", line_separator);
    }

    /**
     * Writes a decorative header for the statistics report file.
     */
    void ReportGenerator::write_header()
    {
        if (!stats_out.is_open())
            return;

        std::string border(43, '=');
        stats_out << std::format("{}\n", border);
        stats_out << "       BIOINFO PARSER - ANALYSIS REPORT      \n";
        stats_out << std::format("{}\n\n", border);
    }

} // namespace BioInfoParser