#include <iostream>
#include <string>
#include <bitset>
using namespace std;
#define VAR 491
#define DVAR 982

class Poly {

bitset<VAR> cf;
const size_t bit_length;


public:
Poly() : cf{0b0}, bit_length{VAR} {}

Poly( string& stringx) : bit_length{VAR} 
{
    int len = stringx.size() - 1;
    
    if(len >= VAR)
        return; 
    
    int i = 0;
    for(auto var = stringx.end() - 1; len >= 0; --len, --var)
    {
        if(*var == '1')
            cf[i] = 1;
        else if(*var != '0')
        {
            cf = 0b0;
            return;
        }

        i++;
    }
}


size_t FP() const
{
    return bit_length;
}

string to_string() const
{

    string res = "";
    bool tr = false;
    for(int i = VAR - 1; i >= 0; --i)
    {
        if(tr)
            res += this->cf[i] ? '1' : '0';
        else if(tr = this->cf[i])
            res += '1';
    }

    if(res.size() == 0)
        return "0";

    return res;
}

bitset<DVAR> dsize(const bitset<VAR>& st)
{
    bitset<DVAR> result;
    for(int i = 0; i < VAR; ++i)
        result[i] = st[i];

    return result;
}

bitset<VAR> shrink(const bitset<DVAR>& st)
{
    bitset<VAR> result;
    for(int i = 0; i < VAR; ++i)
        result[i] = st[i];

    return result;
}

void mod(bitset<DVAR>& value)
{

    bitset<DVAR> p;
    p[VAR] = p[17] = p[6] = p[2] = p[0] = 1;
    

    for(int i = DVAR - 1; i >= VAR; --i)
    {
        if(value[i])
            value ^= (p << i - VAR);
    }
}

Poly square()
{
    bitset<DVAR> res;
   
    for(int i = 0; i < VAR; ++i)
        res[i << 1] = this->cf[i];

    mod(res);

    return Poly(shrink(res));
}

void in_square()
{
    bitset<DVAR> res;

    for(int i = 0; i < VAR; ++i)
        res[i << 1] = this->cf[i];

    
    mod(res);
    this->cf = shrink(res);
}

Poly trace(const Poly& poly)
{

    Poly result = poly;
    Poly current_conjugate = poly;
    for(int i = 1; i < VAR; ++i)
    {
        current_conjugate = current_conjugate.square();
        result.cf ^= current_conjugate.cf;
    }
    
    return result;
}

Poly inverse() const
{
    
    Poly result = 1;
    

    for(int i = 1; i < VAR; ++i)
    {
        result = result * *this;
        result.in_square();    
    }

    return result;
}



Poly & operator=(const Poly& x)
{
    this->cf = x.cf;
    return *this; 
}

Poly operator+(const Poly& x) const
{
    Poly res;

    res.cf = this->cf ^ x.cf;

    return res; 
}

Poly operator*(const Poly& right) 
{

    bitset<DVAR> mrc;

    bitset<DVAR> l = dsize(this->cf);
    bitset<DVAR> r = dsize(right.cf);

    for(int i = 0; i < DVAR; ++i, l <<= 1)
    {   
        if(r[i])
            mrc ^= l;
    }

    mod(mrc);

    return Poly(shrink(mrc));
}

bool operator==(const Poly& x) const
{
    return this->cf == x.cf;
}

bitset<VAR> str(const string& x)
{
    bitset<VAR> res;
    int len = x.size() - 3;
    if(len > VAR)
        return 0b0;

    int i = 0;
    for(auto var = x.end() - 1; len >= 0; --len, --var)
    {
        if(*var == '1')
            res[i] = 1;
        else if(*var != '0')
        {
            return 0b0;
        }

        i++;
    }


    return res;
}

Poly power(const string& pow) 
{
    bitset<VAR> c_pow = str(pow);
    Poly result = 1;

    for(int i = VAR - 1; i > 0; --i)
    {
        if(c_pow[i])
            result = result * *this;

        result.in_square();    
    }

    if(c_pow[0])
        result = result * *this;

    return result;
}
std::ostream& printa(std::ostream& out, const Poly& p)
{
    return out << p.to_string();
}

private:


};

int main()
{
    string a1 = "01100111100010011111000110100011000101110111001101110111111000001100011100001101101011001111011001001101100101010110000111110110001111011010100111011100010100100101111000110001100111110100001110110010010100000111001101010100101111001011001001000010101110010010001011001101001011011010100010011110011010001101011111011010111000110010000110101001010100110100101101110000001111100000110001101000100111011001011001011001001010111110110111101100011001110100001001110111111100001100000001000110111";
    string b1 = "10010010001100010011100101101100011110010000001101100100101010010001011110110011000000111101000011111100110111000100111010001000100101101100000101000111111000110110110111010000111101110000100101100110000010011001110001011000010011110101100100001100010011011110001011101001100001101111011111100100110100010100110110101011001101110111110100010000101011111001010010101100001101010011111111100001111010100110100010010111001000110111110011101001001000001110000001111111001001111000001111101110011";
    cout << "Input A: " << a1 << endl;
    cout << "Input B: " << b1 << endl;
    string pow = "00111100111001000011110010010111010110111001011011000010010101100010111010101111001111111100110010001110100111110001111011101010010000101011010110001000011100110001101111001001000111100011101010110011100010000110000001010101111101000111110111010110101000101111011000011011111011001111011101010111110101001000001110010000010010010011010000110001001011100000100111110000010110000100100101101100010000101110010100100101100011010111101110010100111100100010000101101001011111001110110101100000010";
    cout << "Input POW: " << pow << endl;
    Poly a(a1);
    Poly b(b1);

    cout << "Converted A: " + a.to_string()<< endl;
   
    cout << "Converted B:" + b.to_string() << endl;    

    cout << "A + B: " + (a + b).to_string() << endl;
    cout << "A * B: " + (a * b).to_string()<< endl;
    cout << "A^-1 : " + (a.inverse()).to_string() << endl;
    cout << (a.inverse() * a).to_string() << endl;
    cout << "B^-1 : " + (b.inverse()).to_string() << endl;
    cout << (b.inverse() * b).to_string() << endl;
    cout << "A^2 : " << a.square().to_string() << endl;
    cout << (a.square() == a*a) << endl;
    cout << "A^POW:" << a.power(pow).to_string() << endl;
    cout << "Tr(A): " + (a.trace(a)).to_string() << endl;
}