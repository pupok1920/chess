#ifndef __VALIDATORSVUIHVEUVJKDVSBVKSVDJ__
#define __VALIDATORSVUIHVEUVJKDVSBVKSVDJ__

class Data;
class Square;

class Validator {
public:
    Validator();
    ~Validator();

    bool isMoveValid(const Data *data, const Square &from,
            const Square &to) const;
};
#endif
