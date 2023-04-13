class Number{
public:
    Number(long long);
    Number(const Number &);
    Number(Number &&);
    virtual Number & operator = (const Number &);
    virtual Number & operator = (Number &&);
    virtual Number operator + (const Number &);
    virtual Number operator - (const Number &);
    virtual Number operator * (const Number &);
    virtual Number operator / (const Number &);
    virtual Number operator ^ (const Number &);
    virtual Number operator | (const Number &);
    virtual Number operator & (const Number &);
    virtual bool operator < (const Number &);
    virtual bool operator > (const Number &);
    virtual bool operator == (const Number &);
    virtual Number & operator += (const Number &);
    virtual Number & operator -= (const Number &);
    virtual Number & operator *= (const Number &);
    virtual Number & operator /= (const Number &);
    virtual Number & operator ^= (const Number &);
    virtual Number & operator |= (const Number &);
    virtual Number & operator &= (const Number &);
};
