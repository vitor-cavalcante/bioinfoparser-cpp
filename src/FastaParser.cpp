/*
 * Project: BioInfoParser-CPP
 * Author: Vitor Cavalcante
 * License: MIT
 */

#include "FastaParser.hpp"
#include <stdexcept>
#include <string>

namespace BioInfoParser
{

    /**
     * Constructor: Opens the FASTA file and validates the stream.
     * Throws a runtime_error if the file cannot be accessed.
     */
    FastaParser::FastaParser(const std::string &filepath) : input_file(filepath)
    {
        if (!input_file.is_open())
        {
            throw std::runtime_error("Could not open FASTA file at: " + filepath);
        }
    }

    /**
     * Destructor: Ensures the file stream is closed to release system resources.
     */
    FastaParser::~FastaParser()
    {
        if (input_file.is_open())
        {
            input_file.close();
        }
    }

    /**
     * Parses and returns the next available biological sequence from the file.
     * Uses a buffering strategy (last_line) to handle the multi-line FASTA format.
     */
    std::optional<BioSequence> FastaParser::get_next_sequence()
    {
        std::string id;
        std::string full_sequence;
        std::string line;

        // Check if we have a header stored from a previous read operation
        if (!last_line.empty() && last_line[0] == '>')
        {
            id = last_line.substr(1); // Extract ID by removing the '>' prefix
            last_line.clear();
        }

        // Read the file line by line
        while (std::getline(input_file, line))
        {
            if (line.empty())
                continue; // Skip blank lines

            if (line[0] == '>')
            {
                // If we find a new header and already have an active ID,
                // it means the current sequence is finished.
                if (!id.empty())
                {
                    last_line = line; // Store this header for the next call
                    return BioSequence(id, full_sequence);
                }
                // Otherwise, this is the first ID we've encountered
                id = line.substr(1);
            }
            else
            {
                // Append sequence data lines to the main sequence string
                full_sequence += line;
            }
        }

        // Return the final sequence at the end of the file
        if (!id.empty())
        {
            return BioSequence(id, full_sequence);
        }

        return std::nullopt; // End of file reached with no data
    }

    /**
     * Determines if there is more data to be processed.
     * The parser is not finished if the file is open or if a header is still buffered.
     */
    bool FastaParser::has_more_sequences()
    {
        return !input_file.eof() || !last_line.empty();
    }

} // namespace BioInfoParser