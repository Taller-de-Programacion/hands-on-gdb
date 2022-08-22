#include "cmds.h"

IntSetController::IntSetController(std::istream &in, std::ostream &out, std::ostream &err) : in(in), out(out), err(err) {}

int IntSetController::process(int limit) {
    int num = 0;
    char cmd;
    int val;

    out << std::boolalpha;

    in >> cmd;
    while (in) {
        switch (cmd) {
            case 'a':
                in >> val;
                out << val << " added, was already in the set? " << set.add(val) << "\n";
                break;
            case 'h':
                in >> val;
                out << "is " << val << " in the set? " << set.has(val) << "\n";
                break;
            case 'C':
                out << "count: " << set.count() << "\n";
                break;
            case 'x':
                set.clear();
                out << "cleared\n";
                break;
            case 'l':
                out << "list:";
                for (const int n : set.as_list()) {
                    out << " " << n;
                }
                out << "\n";
                break;
            default:
                err << "Error, unexpected command '" << cmd << "'\n";
                return -1;
        }

        num += 1;
        if (limit > 0 and num >= limit)
            break;

        in >> cmd;
    }

    return 0;
}
