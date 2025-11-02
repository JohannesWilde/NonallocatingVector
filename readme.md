# This project started with the following goal:

Simple project trying to explore a "view-only" vector for a pre-allocated storage.

I need something like this to have a performant interface between C and an existing C++ interface, which uses `std::vector` as input.

# Result

However my custom-allocated vector could not be used with legacy code expecting `std::vector<T, std::allocator>` [see b9644fb38dcf5e1203e83a34995d89d04b0e6f09] - so I chose to use `std::span` instead.
