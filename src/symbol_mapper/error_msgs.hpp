#ifndef error_msgs_hpp
#define error_msgs_hpp

#include <iostream>
#include <string>

const string BPSK = "bpsk",
             QPSK = "qpsk",
             PSK8 = "8psk",
             PSK16 = "16psk",
             PSK256 = "256psk";

/**
 * Name: error
 * Purpose: A utility class (a class that is never meant to be instantiated by itself) containing all
 *          error messages. This class really just serves as a means of grouping the error messages
 *          together in one place. However, since it wouldn't make sense to instantiate an object of
 *          this class, the destructor has been declared as what's known as a "pure virtual function",
 *          and therefore unable to be instantiated. All functions have been declared static, so they
 *          may be used outside of the class.
 */
class error {
    public:
        virtual ~error() = 0;   //turns this class into a Utility class
        static void how_to ();
        static void invalid_num_arguments ();
        static void invalid_num_samples_msg ();
        static void accepted_mod_types_msg ();
        static void mod_type_missing_msg ();
        static void invalid_mod_type_msg ();
};

/**
 * Name: how_to
 * Purpose: Displays a message showing how the symbol mapper program is intended to be used on the
 *          command line.
 */
void error::how_to ()
{
    cerr << endl
         << "Usage: cat <inputfile> | ./symbol_mapper <# samples/symbol> <modulation type> [--debug]"
         << endl;
}

/**
 * Name: invalid_num_arguments
 * Purpose: Displays an error message that the number of arguments given to the symbol mapper program
 *          is invalid (none or too many).
 */
void error::invalid_num_arguments ()
{
    cerr << endl
         << "Symbol Mapping Error: Invalid number of arguments provided.";
    how_to();
    exit(EXIT_FAILURE);
}

/**
 * Name: invalid_num_samples_msg
 * Purpose: Displays an error message that the number of samples per symbol command line argument is
 *          invalid (<= 0).
 */
void error::invalid_num_samples_msg ()
{
    cerr << endl
         << "Symbol Mapping Error: Invalid number of samples per symbol." << endl
         << "                      Number of samples must be greater than 0.";
    how_to();
    exit(EXIT_FAILURE);
}

/**
 * Name: accepted_mod_types_msg
 * Purpose: Displays a message showing the accepted modulation techniques for the symbol mapper.
 */
void error::accepted_mod_types_msg ()
{
    cerr << endl
         << "Accepted modulation techniques:" << endl
         << "   " << BPSK << endl
         << "   " << QPSK << endl
         << "   " << PSK16 << endl
         << "   " << PSK256;
}

/**
 * Name: mod_type_missing_msg
 * Purpose: Displays a message the modulation type was not given as an argument when the symbol mapper
 *          was run on the command line.
 */
void error::mod_type_missing_msg ()
{
    cerr << endl
         << "Symbol Mapping Error: Missing modulation technique.";
    accepted_mod_types_msg();
    how_to();
    exit(EXIT_FAILURE);
}

/**
 * Name: invalid_mod_type_msg
 * Purpose: Displays an error message that the modulation technique is invalid before displaying the
 *          valid techniques that can be entered.
 */
void error::invalid_mod_type_msg ()
{
    cerr << endl
             << "Symbol Mapping Error: Invalid modulation technique.";
    accepted_mod_types_msg();
    how_to();
    exit(EXIT_FAILURE);
}

#endif
