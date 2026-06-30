/*
 * Milestone 1: Mini Database
 * ==========================
 *
 * Goal
 * ----
 * Build the first working version of a small database program. Keep this
 * milestone simple: store records in memory, let the user work with them,
 * and print clear results. Do not add advanced features until the basic
 * version works correctly.
 *
 * What to implement
 * -----------------
 * 1. Define a record.
 *    - Use a struct or class.
 *    - Add the fields required by the assignment.
 *    - Give each record a value that can be used to identify it.
 *
 * 2. Store the records.
 *    - Choose a standard C++ container, such as std::vector.
 *    - Keep all records in that container while the program is running.
 *
 * 3. Add the required database operations.
 *    - Add a new record.
 *    - Display the stored records.
 *    - Find a record by its identifying value.
 *    - Add update or delete only if Milestone 1 requires them.
 *
 * 4. Create a simple user interface.
 *    - Show a numbered menu.
 *    - Read the user's choice and any required record information.
 *    - Run the matching operation.
 *    - Keep showing the menu until the user chooses to exit.
 *
 * 5. Handle simple errors.
 *    - Reject invalid menu choices.
 *    - Do not add a record if its identifying value must be unique and is
 *      already in use.
 *    - Print a friendly message when a requested record cannot be found.
 *    - Make sure bad input does not leave the program in a broken state.
 *
 * Suggested order
 * ---------------
 * 1. Write the record type.
 * 2. Write and test one operation at a time.
 * 3. Add the menu after the operations work.
 * 4. Test empty data, one record, several records, duplicate identifiers,
 *    missing records, and invalid input.
 *
 * Keep the code readable: use small functions, clear names, and short
 * comments that explain why something is done. This file is intentionally
 * not implemented yet.
 */
