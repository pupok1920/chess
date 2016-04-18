#pragma once

template <typename Container> class ListPublisher {
public:
  typedef typename Container::value_type value_type;
  typedef std::function<QVariant(value_type const &)> roleFn;

  template <typename QListModel>
  void set(Container const &nModel, QListModel &list) {
    for (size_t i = 0; i < nModel.size() && i < model.size(); ++i) {
      if (nModel[i] == model[i])
        continue;

      model[i] = nModel[i];

      QModelIndex topLeft = list.createIndex(i, 0);
      QModelIndex bottomRight = list.createIndex(i, 0);
      emit list.dataChanged(topLeft, bottomRight);
    }

    if (model.size() < nModel.size()) {
      list.beginInsertRows(QModelIndex(), model.size(), nModel.size() - 1);
      model.insert(model.end(), nModel.begin() + model.size(), nModel.end());
      list.endInsertRows();
    }

    if (model.size() > nModel.size()) {
      list.beginRemoveRows(QModelIndex(), nModel.size(), model.size() - 1);
      model.erase(model.begin() + nModel.size(), model.end());
      list.endRemoveRows();
    }
  }

  Container const &get() const { return model; }

  void addRole(std::string const &name, roleFn const &&fn) {
    roles.push_back(std::make_pair(name, fn));
  }

  QVariant data(const QModelIndex &modelIndex, int role) const {
    if (!modelIndex.isValid()) {
      return QVariant();
    }

    size_t index = static_cast<size_t>(modelIndex.row());
    size_t urole = static_cast<size_t>(role - FIRST_ROLE_INDEX);

    try {
      return roles.at(urole).second(model.at(index));
    } catch (...) {
    }
    return QVariant();
  }

  QHash<int, QByteArray> roleNames() const {
    QHash<int, QByteArray> result;

    int index = FIRST_ROLE_INDEX;

    for (auto const &i : roles) {
      result[index++] = i.first.c_str();
    }

    return result;
  }

private:
  enum { FIRST_ROLE_INDEX = Qt::UserRole + 1 };


  std::vector<std::pair<std::string, roleFn>> roles;
  Container model;
};
