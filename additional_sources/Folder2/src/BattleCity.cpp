#include "BattleCity.h"
#include "ListPublisher.h"
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <deque>
#include <functional>
#include <complex>
#include <QKeyEvent>
#include <QTimer>
#include <stdlib.h>

namespace {

const int ENEMY_LEFT = 30;
const size_t FIRE_TICK_DELAY = 100;
const int CREATE_ENEMY_TICK_DELAY = 200;
const int WORLD_SIZE = 13;
const double TANK_SPEED = 0.025;
const double BULLET_SPEED = 0.1;

const std::complex<double>
  DIR_UP   ( 0,-1),
  DIR_DOWN ( 0, 1),
  DIR_LEFT (-1, 0),
  DIR_RIGHT( 1, 0);

std::complex<double> randDirection()
{
  static std::vector<std::complex<double>> v = {
    DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN
  };
  return v[rand() % v.size()];
}

struct UniqId {
  size_t get() const { return id; }

  UniqId() {
    static size_t tmp = 0;
    id = ++tmp;
  }

private:
  size_t id;
};

template <typename P, typename B, typename E>
bool pointOutOfRange(P &p, B begin, E end) {
  if (p.real() > end) {
    p.real(end);
    return true;
  }

  if (p.real() < begin) {
    p.real(begin);
    return true;
  }

  if (p.imag() > end) {
    p.imag(end);
    return true;
  }

  if (p.imag() < begin) {
    p.imag(begin);
    return true;
  }
  return false;
}

struct World {
  struct Object {
    enum class Type {
      BULLET,
      WALL1,
      WALL2,
      HOME,
      TANK_PLAYER,
      TANK_ENEMY,
    };

    typedef std::function<void(Object &)> Delegate;

    Object() : linkedObj(0), dead(false){};

    Object(Object::Type type, double x, double y, double speed, Delegate delegate = Delegate())
      : linkedObj(0)
      , direction(0,-1)
      , position(x,y)
      , speed(speed)
      , type(type)
      , subType(type)
      , canMove(false)
      , dead(false)
      , delegate(delegate)
      { }

    bool operator==(const Object &rh) const {
      return position == rh.position && direction == rh.direction &&
             type == rh.type && dead == rh.dead;
    }

    void update() {
      if (delegate)
        delegate(*this);

      if (0 == direction.real())
        position.real(static_cast<int>(position.real() + 0.5));
      if (0 == direction.imag())
        position.imag(static_cast<int>(position.imag() + 0.5));

      position += direction * speed;
    }

    void die() {
      Delegate().swap(delegate);
      dead = true;
      speed = 0;
    }

    UniqId id;
    size_t linkedObj;
    std::complex<double> direction;
    std::complex<double> position;
    double speed;
    Type type;
    Type subType;
    bool canMove;
    bool dead;
    Delegate delegate;
  };

  typedef std::vector<Object> Objects;

  bool gameOver() const;

  void fire(Object &object);
  void ai(Object &object);
  void update();
  void createEnemy();

  size_t interspect(Object const &obj);
  bool canFire(const Object &object) const;

  Objects objects;
  size_t enemyLeft;
};

void World::createEnemy()
{
  if (!enemyLeft) {
    return;
  }

  if ((rand() % CREATE_ENEMY_TICK_DELAY)) {
    return;
  }

  for(int i =0; i< WORLD_SIZE; ++i)
  {
    Object enemy(Object::Type::TANK_ENEMY, rand() % WORLD_SIZE, 0, TANK_SPEED, [&](Object& o) { ai(o); });

    if (objects.size() != interspect(enemy)) {
      continue;
    }

    objects.push_back(enemy);
    --enemyLeft;

    break;
  }
}

bool World::canFire(const Object &obj) const {
  for (auto &a : objects) {
    if (a.linkedObj == obj.id.get())
      return false;
  }

  return true;
}

void World::fire(Object &object) {
  if (!canFire(object)) {
    return;
  }

  Object bullet(Object::Type::BULLET, 0, 0, BULLET_SPEED);
  bullet.linkedObj = object.id.get();
  bullet.direction = object.direction;
  bullet.position = object.position + bullet.direction * bullet.speed;
  bullet.subType = object.subType;

  objects.push_back(bullet);
}

void World::ai(Object &object) {
  if (!object.canMove) {
    object.canMove = true;
    object.direction = randDirection();
    fire(object);
  }

  if (!(rand() % FIRE_TICK_DELAY)) {
    fire(object);
  }
}

size_t World::interspect(Object const &obj) {
  if (obj.dead)
    return objects.size();

  for (size_t i = 0; i < objects.size(); ++i) {
    if (objects[i].dead) {
      continue;
    }

    if (objects[i].id.get() == obj.id.get()) {
      continue;
    }

    if (objects[i].linkedObj == obj.id.get()) {
      continue;
    }

    if (obj.linkedObj == objects[i].id.get()) {
      continue;
    }

    double maxDistance = 1.;

    if (obj.type == Object::Type::BULLET || objects[i].type == Object::Type::BULLET) {
      maxDistance = 0.25;
    }

    if (std::abs(obj.position - objects[i].position) < maxDistance) {
      return i;
    }
  }
  return objects.size();
}

bool World::gameOver() const {
  for (auto i : objects) {
    if (Object::Type::HOME == i.type && i.dead) {
      return true;
    }
    if (Object::Type::TANK_PLAYER == i.type && i.dead) {
      return true;
    }
  }
  return false;
}

void World::update() {
  createEnemy();

  for (size_t i = 0; i < objects.size(); ++i) {

    auto position = objects[i].position;

    objects[i].update();

    if (position == objects[i].position) {
      continue;
    }

    // check for range
    if (pointOutOfRange(objects[i].position, 0, WORLD_SIZE - 1)) {
      objects[i].canMove = false;

      if (Object::Type::BULLET == objects[i].type) {
        objects[i].die();
      }
      continue;
    }

    size_t o = interspect(objects[i]);

    if (o == objects.size()) {
      continue;
    }

    if (Object::Type::BULLET != objects[i].type &&
        Object::Type::BULLET != objects[o].type) {
      objects[i].position = position;
      objects[i].canMove = false;
      continue;
    }

    if (objects[i].subType == objects[o].subType) {
      continue;
    }

    if (Object::Type::WALL2 == objects[i].type ||
        Object::Type::WALL2 == objects[o].type) {
      continue;
    }

    objects[o].die();
    objects[i].die();
  }

  Objects tmp;

  std::copy_if(objects.begin(), objects.end(), std::back_inserter(tmp),
               [](Object &o) { return o.dead && o.type != Object::Type::BULLET; });

  std::copy_if(objects.begin(), objects.end(), std::back_inserter(tmp),
               [](Object &o) { return !o.dead; });

  tmp.swap(objects);
}

} // namespace

class BattleCity::Implementation : public World {
public:
  enum { FIRST_ROLE_INDEX = Qt::UserRole + 1 };

  std::vector<std::pair<std::string, std::function<QVariant(Object const &)>>> roles;

  void load();

  void processEvent(Object &);

  ListPublisher<Objects> publishedModel;

  QTimer timer;

  std::map<int, bool> events;
  unsigned char keymask = 0;

  size_t enemyLeftTracer;
  bool gameOverTracer;
};

void BattleCity::Implementation::load() {
  static const std::vector<std::string> initPosition = {
    {"e     e     e"},
    {" # # # # # # "},
    {" # # # # # # "},
    {"222222222# # "},
    {" # # # # # # "},
    {" # #222222222"},
    {"     # #     "},
    {"# #   #  ## #"},
    {"22222222 ##22"},
    {"#############"},
    {"#############"},
    {"     ###     "},
    {"    p#x#     "},
  };

  using std::placeholders::_1;

  enemyLeft = ENEMY_LEFT;

  auto enemy = [&](double x, double y) {
    --enemyLeft;
    return Object(Object::Type::TANK_ENEMY, x, y, TANK_SPEED, std::bind(&Implementation::ai,this,_1));
  };

  auto player = [&] (double x, double y) {
    return Object(Object::Type::TANK_PLAYER, x, y, TANK_SPEED, std::bind(&Implementation::processEvent,this,_1));
  };

  auto home = [&] (double x, double y) {
    return Object(Object::Type::HOME, x, y, 0);
  };

  auto wall = [&] (double x, double y) {
    return Object(Object::Type::WALL1, x, y, 0);
  };
  auto wall2 = [&] (double x, double y) {
    return Object(Object::Type::WALL2, x, y, 0);
  };

  std::map<char, std::function<Object(double, double)>>  factory = {
    {'x', home  },
    {'p', player},
    {'e', enemy },
    {'#', wall  },
    {'2', wall2 },
  };

  objects.clear();

  for (size_t i = 0; i < initPosition.size(); ++i)
    for (size_t j = 0; j < initPosition[i].size(); ++j)
      try { objects.push_back(factory.at(initPosition[i][j])(j, i)); }
      catch(std::out_of_range const&) { } // skeep empty cell
}

void BattleCity::Implementation::processEvent(Object &o) {
    o.speed = TANK_SPEED;

         if (events[Qt::Key_Left ])  o.direction = DIR_LEFT ;
    else if (events[Qt::Key_Right])  o.direction = DIR_RIGHT;
    else if (events[Qt::Key_Up   ])  o.direction = DIR_UP   ;
    else if (events[Qt::Key_Down ])  o.direction = DIR_DOWN ;
    else                             o.speed     =        0 ;

    if (events[Qt::Key_Space]) {
      fire(o);
      events[Qt::Key_Space] = false;
    }
}

BattleCity::BattleCity()
    : impl(new Implementation()) //(std::make_unique<Implementation>())
{
  connect(&(impl->timer), SIGNAL(timeout()), this, SLOT(tickUpdate()));

  typedef Implementation::Object Object;

  impl->publishedModel.addRole("posX", [&] (Object const& obj) {
    return QVariant(obj.position.real());
  });

  impl->publishedModel.addRole("posY", [&] (Object const& obj) {
    return QVariant(obj.position.imag());
  });

  impl->publishedModel.addRole("type", [&] (Object const& obj) {
    return QVariant(static_cast<int>(obj.type));
  });

  impl->publishedModel.addRole("arg", [&] (Object const& obj) {
    return std::arg(obj.direction);
  });

  impl->publishedModel.addRole("dead", [&] (Object const& obj) {
    return obj.dead;
  });

  impl->load();
  impl->timer.start(10);
}

BattleCity::~BattleCity() {}

int BattleCity::rowCount(const QModelIndex &) const {
  return impl->publishedModel.get().size();
}

QVariant BattleCity::data(const QModelIndex &modelIndex, int role) const {
  return impl->publishedModel.data(modelIndex, role);
}

QHash<int, QByteArray> BattleCity::roleNames() const {
  return impl->publishedModel.roleNames();
}

void BattleCity::publishModel() {
    impl->publishedModel.set(impl->objects, *this);

    if(impl->enemyLeftTracer != impl->enemyLeft) {
      impl->enemyLeftTracer = impl->enemyLeft;
      enemyLeftChanged();
    }

    if(impl->gameOverTracer != impl->gameOver()) {
      impl->gameOverTracer = impl->gameOver();
      gameOverChanged();
    }
}

void BattleCity::tickUpdate() {
  if (impl->gameOver()) {
    return;
  }
  impl->update();
  publishModel();
}

void BattleCity::event(QKeyEvent &event) {
    bool pressed = Qt::Key_Space == event.key() ? true : QEvent::KeyPress == event.type();
    impl->events[event.key()] = pressed;
}

int BattleCity::worldSize() const { return WORLD_SIZE; }
int BattleCity::enemyLeft() const { return impl->enemyLeft; }
bool BattleCity::gameOver() const { return impl->gameOver(); }

void BattleCity::start() {
  if (impl->objects.size()) {
    impl->objects.clear();
    publishModel();
  }
  impl->load();
}
