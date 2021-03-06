#ifndef METALANG99_PRIV_VARIADICS_GET_H
#define METALANG99_PRIV_VARIADICS_GET_H

#define METALANG99_PRIV_VARIADICS_HEAD(...)        METALANG99_PRIV_VARIADICS_HEAD_AUX(__VA_ARGS__, ~)
#define METALANG99_PRIV_VARIADICS_HEAD_AUX(x, ...) x

#define METALANG99_PRIV_VARIADICS_TAIL(...)         METALANG99_PRIV_VARIADICS_TAIL_AUX(__VA_ARGS__)
#define METALANG99_PRIV_VARIADICS_TAIL_AUX(_x, ...) __VA_ARGS__

#define METALANG99_PRIV_VARIADICS_SND(...)            METALANG99_PRIV_VARIADICS_SND_AUX(__VA_ARGS__)
#define METALANG99_PRIV_VARIADICS_SND_AUX(_x, y, ...) y

#endif // METALANG99_PRIV_VARIADICS_GET_H
