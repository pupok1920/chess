#include <QHostAddress>

#include "consts.h"

struct Player{
  PieceColor color;
  QHostAddress addr;
  quint16 port;
};

struct ServerInfo{
  QHostAddress addr;
  quint16 port;
};
