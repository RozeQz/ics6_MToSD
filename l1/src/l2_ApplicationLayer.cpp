/* Программа-заготовка для домашнего задания
 */

#include "hw/l2_ApplicationLayer.h"

using namespace std;

inline const string DATA_DEFAULT_NAME = "lab.data";

bool Application::performCommand(const vector<string> &args)
{
    if (args.empty())
        return false;

    if (args[0] == "l" || args[0] == "load")
    {
        string filename = (args.size() == 1) ? DATA_DEFAULT_NAME : args[1];

        if (!_col.loadCollection(filename))
        {
            _out.Output("Error while loading file '" + filename + "'");
            return false;
        }

        return true;
    }

    if (args[0] == "s" || args[0] == "save")
    {
        string filename = (args.size() == 1) ? DATA_DEFAULT_NAME : args[1];

        if (!_col.saveCollection(filename))
        {
            _out.Output("Error while saving file '" + filename + "'");
            return false;
        }

        return true;
    }

    if (args[0] == "c" || args[0] == "clean")
    {
        if (args.size() != 1)
        {
            _out.Output("Incorrect arguments count for clean command");
            return false;
        }

        _col.clean();

        return true;
    }

    if (args[0] == "a" || args[0] == "add")
    {
        if (args.size() != 6)
        {
            _out.Output("Incorrect arguments count for add command");
            return false;
        }

        _col.addItem(make_shared<Course>(args[1].c_str(), args[2].c_str(), stoul(args[3]), stoul(args[4]), stoul(args[5])));
        return true;
    }

    if (args[0] == "r" || args[0] == "remove")
    {
        if (args.size() != 2)
        {
            _out.Output("Incorrect arguments count for remove command");
            return false;
        }

        _col.removeItem(stoul(args[1]));
        return true;
    }

    if (args[0] == "u" || args[0] == "update")
    {
        if (args.size() != 7)
        {
            _out.Output("Incorrect arguments count for update command");
            return false;
        }

        _col.updateItem(stoul(args[1]), make_shared<Course>(args[2].c_str(), args[3].c_str(), stoul(args[4]), stoul(args[5]), stoul(args[6])));
        return true;
    }

    if (args[0] == "v" || args[0] == "view")
    {
        if (args.size() != 1)
        {
            _out.Output("Incorrect arguments count for view command");
            return false;
        }

        size_t count = 0;
        for (size_t i = 0; i < _col.getSize(); ++i)
        {
            const Course &item = static_cast<Course &>(*_col.getItem(i));

            if (!_col.isRemoved(i))
            {
                _out.Output("[" + to_string(i) + "] " + item.getName() + " " + item.getLanguage() + " " + to_string(item.getDifficulty()) + " " + to_string(item.getDuration()) + " " + to_string(item.getCost()));
                count++;
            }
        }

        _out.Output("The number of elements in the collection: " + to_string(count));
        return true;
    }

    _out.Output("Wrong command '" + args[0] + "'");
    return false;
}
