def update_shared_dict_entry(shared_dict, entry, update_dict):
    shared_dict.update({entry: update_dict[entry]})


def update_shared_dict_entry_item(shared_dict, entry, key, value):
    if entry in shared_dict.keys():
        entry_dict = shared_dict[entry]
        entry_dict[key] = value
        shared_dict.update({entry: entry_dict})
