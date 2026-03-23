/*
 * Project: BioInfoParser-CPP
 * Author: Vitor Cavalcante
 * License: MIT
 */

#include <iostream>
#include <string>
#include <vector>
#include <format> // C++20 formatting: More compatible with MSVC
#include <stdexcept>
#include "FastaParser.hpp"
#include "ReportGenerator.hpp"

/**
 * Main entry point for the BioInfoParser-CPP CLI tool.
 * This program handles FASTA file parsing, biological sequence analysis,
 * and automated report generation.
 */
int main(int argc, char *argv[])
{
    std::string input_path;
    std::string output_base;

    // 1. Argument Parsing: Scan for --input and --output flags.
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "--input" && i + 1 < argc)
        {
            input_path = argv[++i];
        }
        else if (arg == "--output" && i + 1 < argc)
        {
            output_base = argv[++i];
        }
    }

    // Validation: Ensure mandatory command-line arguments are present.
    if (input_path.empty() || output_base.empty())
    {
        std::cerr << "Usage: ./bio_parser --input <file.fasta> --output <base_name>\n";
        return 1;
    }

    try
    {
        // 2. Component Initialization:
        BioInfoParser::FastaParser parser(input_path);
        BioInfoParser::ReportGenerator generator(output_base);

        int total_sequences = 0;
        int error_count = 0;

        std::cout << std::format("Starting sequence processing for: {}\n\n", input_path);

        // 3. Processing Loop:
        while (parser.has_more_sequences())
        {
            try
            {
                auto seq_opt = parser.get_next_sequence();

                if (seq_opt.has_value())
                {
                    const auto &seq = *seq_opt;

                    // Execute transformations and write to respective output files.
                    generator.write_to_fasta(seq);
                    generator.write_to_stats(seq);

                    total_sequences++;
                    std::cout << std::format("Success: Sequence [{}] processed.\n", seq.get_identifier());
                }
            }
            catch (const std::exception &e)
            {
                // Individual sequence error: Log the warning and continue processing.
                std::cerr << std::format("Warning: Failed to parse sequence. Reason: {}\n", e.what());
                error_count++;
            }
        }

        // 4. Execution Summary:
        // FIX for C7595: Create the separator string outside the format call.
        std::string separator(45, '=');

        std::cout << std::format("\n{}\n", separator);
        std::cout << "BioInfo Analysis Completed!\n";
        std::cout << std::format("Processed sequences: {}\n", total_sequences);

        if (error_count > 0)
        {
            std::cout << std::format("Sequences with errors: {}\n", error_count);
        }

        std::cout << std::format("Output generated: {}.processed.fasta and {}.stats.txt\n", output_base, output_base);
        std::cout << std::format("{}\n", separator);
    }
    catch (const std::exception &e)
    {
        // Fatal system error: Exit the program safely.
        std::cerr << std::format("CRITICAL SYSTEM ERROR: {}\n", e.what());
        return 1;
    }

    return 0;
}