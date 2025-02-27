#include <complex>
#include <vector>
#include <math.h>
#include <stdio.h>

using namespace std;

class lattice_fermi
{
public:
    int lat_x, lat_t, lat_spin;
    int size;
    vector<complex<double>> lattice_vec;
    lattice_fermi(int lat_x, int lat_t, int lat_spin) : lat_x(lat_x), lat_t(lat_t), lat_spin(lat_spin), lattice_vec(lat_x * lat_t * lat_spin)
    {
        size = lattice_vec.size();
    }
    lattice_fermi();
    void clean()
    {
        for (int i = 0; i < size; i++)
            lattice_vec[i] = 0;
    }
    complex<double> &operator[](int i)
    {
        return lattice_vec[i];
    }
    lattice_fermi &operator=(lattice_fermi &a)
    {
        for (int i = 0; i < size; i++)
            this->lattice_vec[i] = a.lattice_vec[i];
        return *this;
    }
    lattice_fermi &operator-(const lattice_fermi &a)
    {
        for (int i = 0; i < size; i++)
            this->lattice_vec[i] = this->lattice_vec[i] - a.lattice_vec[i];
        return *this;
    }

    lattice_fermi &operator+(const lattice_fermi &a)
    {
        for (int i = 0; i < size; i++)
            this->lattice_vec[i] = this->lattice_vec[i] + a.lattice_vec[i];
        return *this;
    }
};

class lattice_gauge
{
public:
    int lat_x, lat_t, lat_d;
    int size;
    vector<complex<double>> lattice_vec_c;
    lattice_gauge(int lat_x, int lat_t, int lat_d) : lat_x(lat_x), lat_t(lat_t), lat_d(lat_d), lattice_vec_c(lat_x * lat_t * lat_d)
    {
        size = lattice_vec_c.size();
    }
    lattice_gauge();
    complex<double> &operator[](int i) // const
    {
        return lattice_vec_c[i];
    }
    lattice_gauge &operator=(lattice_gauge a)
    {

        for (int i = 0; i < size; i++)
            this->lattice_vec_c[i] = a.lattice_vec_c[i];
        return *this;
    }
};

class lattice_propagator
{
public:
    int lat_x, lat_t, lat_spin;
    int size;
    vector<complex<double>> lattice_vec_c;
    lattice_propagator(int lat_x, int lat_t, int lat_spin) : lat_x(lat_x), lat_t(lat_t), lat_spin(lat_spin), lattice_vec_c(lat_x * lat_t * lat_spin * lat_spin)
    {
        size = lattice_vec_c.size();
    }
    lattice_propagator(lattice_propagator &prop) : lattice_propagator(prop.lat_x, prop.lat_t, prop.lat_spin) {};
    lattice_propagator();
    void clean()
    {
        for (int i = 0; i < size; i++)
            lattice_vec_c[i] = 0;
    }
    complex<double> &operator[](int i)
    {
        return lattice_vec_c[i];
    }
    lattice_propagator &operator=(const lattice_propagator &a)
    {

        for (int i = 0; i < size; i++)
            this->lattice_vec_c[i] = a.lattice_vec_c[i];
        return *this;
    }

    lattice_propagator &operator-(const lattice_propagator &a)
    {
        for (int i = 0; i < size; i++)
            this->lattice_vec_c[i] = this->lattice_vec_c[i] - a.lattice_vec_c[i];
        return *this;
    }
};

class lattice_complex
{
public:
    int lat_x, lat_t;
    int size;
    vector<complex<double>> lattice_vec_c;
    lattice_complex(int lat_x, int lat_t) : lat_x(lat_x), lat_t(lat_t), lattice_vec_c(lat_x * lat_t)
    {
        size = lattice_vec_c.size();
    }
    //    lattice_complex(lattice_complex &prop):lattice_complex(prop.lat_x,prop.lat_t){};
    lattice_complex() {};
    void clean()
    {
        for (int i = 0; i < size; i++)
            lattice_vec_c[i] = 0;
    }
    complex<double> &operator[](int i)
    {
        return lattice_vec_c[i];
    }
    lattice_complex &operator=(const lattice_complex &a)
    {

        for (int i = 0; i < size; i++)
            this->lattice_vec_c[i] = a.lattice_vec_c[i];
        return *this;
    }
};

class Gamma_2D
{
public:
    vector<complex<double>> lattice_vec_c;
    Gamma_2D(int ig) : lattice_vec_c(4)
    {
        const complex<double> i(0.0, 1.0);
        if (ig == 0)
        {
            lattice_vec_c[0] = 1;
            lattice_vec_c[1] = 0;
            lattice_vec_c[2] = 0;
            lattice_vec_c[3] = 1;
        }
        if (ig == 1)
        {
            lattice_vec_c[0] = 0;
            lattice_vec_c[1] = 1;
            lattice_vec_c[2] = 1;
            lattice_vec_c[3] = 0;
        }
        if (ig == 2)
        {
            lattice_vec_c[0] = 0;
            lattice_vec_c[1] = i;
            lattice_vec_c[2] = -i;
            lattice_vec_c[3] = 0;
        }
        if (ig == 3)
        {
            lattice_vec_c[0] = i;
            lattice_vec_c[1] = 0;
            lattice_vec_c[2] = 0;
            lattice_vec_c[3] = -i;
        }
    }

    complex<double> &operator[](int i) // const
    {
        return lattice_vec_c[i];
    }
};

lattice_propagator operator*(Gamma_2D &G, lattice_propagator &prop)

{
    lattice_propagator prop1(prop.lat_x, prop.lat_t, prop.lat_spin);
    for (int x = 0; x < prop.lat_x; x++)
        for (int t = 0; t < prop.lat_t; t++)
            for (int s1 = 0; s1 < prop.lat_spin; s1++)
                for (int s2 = 0; s2 < prop.lat_spin; s2++)
                {
                    for (int i = 0; i < prop.lat_spin; i++)
                        prop1[x * prop.lat_t * prop.lat_spin * prop.lat_spin + t * prop.lat_spin * prop.lat_spin + s1 * prop.lat_spin + s2] +=
                            G[s1 * 2 + i] * prop[x * prop.lat_t * prop.lat_spin * prop.lat_spin + t * prop.lat_spin * prop.lat_spin + i * prop.lat_spin + s2];
                }
    return prop1;
}

lattice_propagator operator*(lattice_propagator &prop, Gamma_2D &G)

{
    lattice_propagator prop1(prop.lat_x, prop.lat_t, prop.lat_spin);
    for (int x = 0; x < prop.lat_x; x++)
        for (int t = 0; t < prop.lat_t; t++)
            for (int s1 = 0; s1 < prop.lat_spin; s1++)
                for (int s2 = 0; s2 < prop.lat_spin; s2++)
                {
                    for (int i = 0; i < prop.lat_spin; i++)
                        prop1[x * prop.lat_t * prop.lat_spin * prop.lat_spin + t * prop.lat_spin * prop.lat_spin + s1 * prop.lat_spin + s2] +=
                            G[i * 2 + s2] * prop[x * prop.lat_t * prop.lat_spin * prop.lat_spin + t * prop.lat_spin * prop.lat_spin + s1 * prop.lat_spin + i];
                }
    return prop1;
}

lattice_propagator operator*(lattice_propagator &anti_prop, lattice_propagator &prop)

{
    lattice_propagator prop1(prop.lat_x, prop.lat_t, prop.lat_spin);
    for (int x = 0; x < prop.lat_x; x++)
        for (int t = 0; t < prop.lat_t; t++)
            for (int s1 = 0; s1 < prop.lat_spin; s1++)
                for (int s2 = 0; s2 < prop.lat_spin; s2++)
                {
                    int index = x * prop.lat_t + t;
                    for (int i = 0; i < prop.lat_spin; i++)
                        prop1[((index)*prop.lat_spin + s1) * prop.lat_spin + s2] +=
                            prop[((index)*prop.lat_spin + i) * prop.lat_spin + s2] * anti_prop[((index * prop.lat_spin + s1) * prop.lat_spin + i)];
                }
    return prop1;
}

// Function
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double norm_2(lattice_fermi &s)
{
    complex<double> s1(0.0, 0.0);
    for (int i = 0; i < s.size; i++)
    {
        s1 += s[i] * conj(s[i]);
    }
    return s1.real();
};

double norm_2(lattice_propagator &f)
{

    complex<double> f1(0.0, 0.0);
    for (int i = 0; i < f.size; i++)
    {
        f1 += f[i] * conj(f[i]);
    }
    return f1.real();
};

double norm_2(lattice_complex &f)
{

    complex<double> f1(0.0, 0.0);
    for (int i = 0; i < f.size; i++)
    {
        f1 += f[i] * conj(f[i]);
    }
    return f1.real();
};

complex<double> vector_p(lattice_fermi r1, lattice_fermi r2)
{
    complex<double> ro(0.0, 0.0);
    for (int i = 0; i < r1.size; i++)
    {
        ro += (conj(r1[i]) * r2[i]);
    }
    return ro;
};

void Dslash2(lattice_fermi src, lattice_fermi &dest, lattice_gauge U, const double mass, const bool dag)
{

    dest.clean();
    const double a = 2.0;
    const complex<double> i(0.0, 1.0);
    complex<double> tmp;
    const double Half = 0.5;
    double flag = (dag == true) ? -1 : 1;
    for (int x = 0; x < src.lat_x; x++)
        for (int t = 0; t < src.lat_t; t++)
        {

            // mass term
            for (int s = 0; s < src.lat_spin; s++)
            {
                dest[(x * src.lat_t + t) * 2 + s] += -(a + mass) * src[(x * src.lat_t + t) * 2 + s];
            }

            // backward x
            int b_x = (x + src.lat_x - 1) % src.lat_x;
            tmp = (src[(x * src.lat_t + t) * 2 + 0] + flag * src[(x * src.lat_t + t) * 2 + 1]) * Half * U[(b_x * src.lat_t + t) * 2 + 0];
            dest[(b_x * src.lat_t + t) * 2 + 0] += tmp;
            dest[(b_x * src.lat_t + t) * 2 + 1] += flag * tmp;

            // forward x
            int f_x = (x + 1) % src.lat_x;
            tmp = (src[(x * src.lat_t + t) * 2 + 0] - flag * src[(x * src.lat_t + t) * 2 + 1]) * Half * conj(U[(x * src.lat_t + t) * 2 + 0]);
            dest[(f_x * src.lat_t + t) * 2 + 0] += tmp;
            dest[(f_x * src.lat_t + t) * 2 + 1] -= flag * tmp;

            // backward t
            int b_t = (t + src.lat_t - 1) % src.lat_t;
            tmp = (src[(x * src.lat_t + t) * 2 + 0] + flag * i * src[(x * src.lat_t + t) * 2 + 1]) * Half * U[(x * src.lat_t + b_t) * 2 + 1];
            dest[(x * src.lat_t + b_t) * 2 + 0] += tmp;
            dest[(x * src.lat_t + b_t) * 2 + 1] -= flag * i * tmp;

            // forward t
            int f_t = (t + 1) % src.lat_t;
            tmp = (src[(x * src.lat_t + t) * 2 + 0] - flag * i * src[(x * src.lat_t + t) * 2 + 1]) * Half * conj(U[(x * src.lat_t + t) * 2 + 1]);
            dest[(x * src.lat_t + f_t) * 2 + 0] += tmp;
            dest[(x * src.lat_t + f_t) * 2 + 1] += flag * i * tmp;
        }
    /*
    for (int i=0;i<dest.size;i++)
    {
    dest[i]=-dest[i];
    }
    */
}

void fermi_to_prop(lattice_fermi dest, lattice_propagator &prop, int i)
{
    for (int x = 0; x < dest.lat_x; x++)
        for (int t = 0; t < dest.lat_t; t++)
            for (int s = 0; s < dest.lat_spin; s++)
            {
                prop[(x * prop.lat_t + t) * prop.lat_spin * prop.lat_spin + (i * prop.lat_spin) + s] = dest[(x * prop.lat_t + t) * prop.lat_spin + s];
                //    printf("dest=%f\n",dest[(x*prop.lat_t+t)*prop.lat_spin+s].real());
                //    printf("dest=%f\n",prop[(x*prop.lat_t+t)*prop.lat_spin*prop.lat_spin+(i*prop.lat_spin)+s].real());
            }
}

lattice_propagator adj(lattice_propagator &prop)
{
    lattice_propagator prop_1(prop);

    for (int x = 0; x < prop.lat_x; x++)
        for (int t = 0; t < prop.lat_t; t++)
            for (int s1 = 0; s1 < prop.lat_spin; s1++)
                for (int s2 = 0; s2 < prop.lat_spin; s2++)
                {
                    int index = (x * prop.lat_t + t);
                    prop_1[((index * prop.lat_spin + s1) * prop.lat_spin + s2)] = conj(prop[((index * prop.lat_spin + s2) * prop.lat_spin + s1)]);
                }
    return prop_1;
}

lattice_complex trace(lattice_propagator &prop)
{
    lattice_complex corr(prop.lat_x, prop.lat_t);

    for (int x = 0; x < corr.lat_x; x++)
        for (int t = 0; t < corr.lat_t; t++)
            for (int s1 = 0; s1 < prop.lat_spin; s1++)
                for (int s2 = 0; s2 < prop.lat_spin; s2++)
                {
                    int index = x * corr.lat_t + t;
                    if (s1 == s2)
                    {
                        corr[index] += prop[((index)*prop.lat_spin + s1) * prop.lat_spin + s2];
                    }
                }
    return corr;
}

void hardon(lattice_propagator &prop, lattice_propagator &anti_prop, lattice_complex &corr, int ig1, int ig2)
{
    Gamma_2D G1(ig1);
    Gamma_2D G2(ig2);

    anti_prop = adj(anti_prop);
    anti_prop = anti_prop * G1;
    anti_prop = anti_prop * prop;
    anti_prop = anti_prop * G2;
    corr = trace(anti_prop);
}

vector<complex<double>> SumMulti(lattice_complex &corr)
{
    vector<complex<double>> xsum(corr.lat_t);

    for (int x = 0; x < corr.lat_x; x++)
        for (int t = 0; t < corr.lat_t; t++)
        {
            xsum[t] += corr[x * corr.lat_t + t];
        }
    return xsum;
}

int CG(lattice_fermi src, lattice_fermi &dest, lattice_gauge U, const double mass, const int max)
{
    lattice_fermi r0(src.lat_x, src.lat_t, src.lat_spin);
    lattice_fermi rr0(src.lat_x, src.lat_t, src.lat_spin);
    lattice_fermi z0(src.lat_x, src.lat_t, src.lat_spin);
    lattice_fermi r1(src.lat_x, src.lat_t, src.lat_spin);
    lattice_fermi z1(src.lat_x, src.lat_t, src.lat_spin);
    lattice_fermi q(src.lat_x, src.lat_t, src.lat_spin);
    lattice_fermi qq(src.lat_x, src.lat_t, src.lat_spin);
    lattice_fermi P(src.lat_x, src.lat_t, src.lat_spin);
    complex<double> aphi;
    complex<double> beta;
    for (int i = 0; i < src.size; i++)
    {
        r0[i] = 0;
    }
    for (int i = 0; i < dest.size; i++)
    {
        dest[i] = 0;
    }

    Dslash2(dest, rr0, U, mass, false);
    Dslash2(rr0, r0, U, mass, true);
    for (int i = 0; i < src.size; i++)
    {
        r0[i] = src[i] - r0[i];
    }
    for (int f = 1; f < max; f++)
    {

        printf("iteration=%i\n", f);
        std::complex<double> rho;
        rho = vector_p(r0, r0);

        std::complex<double> rho1;
        rho1 = vector_p(r1, r1);
        for (int i = 0; i < z0.size; i++)
        {
            z0[i] = r0[i];
        }
        if (f == 1)
        {
            for (int i = 0; i < P.size; i++)
            {
                P[i] = z0[i];
            }
            //            printf("P=%f\n",norm_2(P));
        }
        else
        {
            beta = rho / rho1;
            //           printf("beta=%f\n",beta);
            for (int i = 0; i < P.size; i++)
                P[i] = z0[i] + beta * P[i];
            //          printf("P=%f\n",norm_2(P));
        }
        Dslash2(P, qq, U, mass, false);
        //       printf("d_qq=%f\n",norm_2(qq));
        Dslash2(qq, q, U, mass, true);
        //       printf("q=%f\n",norm_2(q));
        aphi = rho / vector_p(P, q);
        //       printf("d_q=%f\n",vector_p(P,q));
        //       printf("aphi=%f\n",aphi);
        for (int i = 0; i < dest.size; i++)
            dest[i] = dest[i] + aphi * P[i];
        for (int i = 0; i < r1.size; i++)
            r1[i] = r0[i];
        for (int i = 0; i < r0.size; i++)
        {
            r0[i] = r0[i] - aphi * q[i];
        }
        printf("norm2(r0)=%.10e\n", norm_2(r0));
        if (norm_2(r0) < 1e-12)
        {
            printf("convergence recedul=1e-12\n");
            return 0;
        }
    } // for (f) end

} // CG func end

// CODE STAR
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    // gird distance
    int nx = 16;
    int nt = 16;
    int ns = 2;
    int nd = 2;
    double mass = 1;

    lattice_fermi src(nx, nt, ns);
    lattice_fermi ssrc(nx, nt, ns);
    lattice_fermi dest(nx, nt, ns);
    lattice_fermi dest_1(nx, nt, ns);
    lattice_fermi src1(nx, nt, ns);
    lattice_gauge U(nx, nt, ns);
    lattice_propagator prop(nx, nt, ns);
    lattice_propagator anti_prop(nx, nt, ns);
    lattice_propagator Prop(nx, nt, ns);
    lattice_complex corr(nx, nt);
    Gamma_2D gamma5(3);

    for (int i = 0; i < U.size; i++)
        U[i] = 1.0;
    for (int i = 0; i < src.size; i++)
        if (i == 0)
            src[i] = 1;
        else
            src[i] = 0;
    for (int i = 0; i < src1.size; i++)
        if (i == 1)
            src1[i] = 1;
        else
            src1[i] = 0;

    Dslash2(src, ssrc, U, mass, true);
    CG(ssrc, dest, U, mass, 1000);

    fermi_to_prop(dest, prop, 0);
    fermi_to_prop(dest_1, prop, 1);

    anti_prop = gamma5 * prop;
    anti_prop = anti_prop * gamma5;

    // Prop=anti_prop*prop;
    hardon(prop, anti_prop, corr, 3, 3);

    for (int i = 0; i < corr.lat_t; i++)
    {
        printf("corr_sum=%f ,%f\n", SumMulti(corr)[i].real(), SumMulti(corr)[i].imag());
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // END CODE
}
