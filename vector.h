struct vector
{
    int x;
    int y;
    int (*set) (int x, int y);
    int size;
};

void cton(struct vector *vec);
void destroy(struct vector *vec);