#define COMMON_SOCKET 10025

enum enum_request{
    FIN = 0,
    FACTORIEL,
    PUISSANCE,
    STATS
};

struct request{
    enum enum_request type;
    int size_request;
};

int creerSocketUDP(int port);

int creerSocketTCP(int port);