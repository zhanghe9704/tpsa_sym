/**
 * @file tpsa_extend.h
 * @brief Extend the original tpsa.h file by Dr. Lingyun Yang.
 * @author He Zhang
 * @email hezhang@jlab.org
 */

#ifndef SYMBTPSA_EXTEND
#define SYMBTPSA_EXTEND

#include <vector>
#include <limits>
#include <cmath>
#include <complex>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <map>

#include "tpsa.h"
#include "symbolic.h"

namespace SymbTPSA{

/** \brief A table that show the relation between the orders and the index of an element in a TPS vector.
 * The orders of an TPS element is a vector of integers that shows the order of each variable in  that element.
 * For example, the element x^3*y*z^2 in a 3D TPS vector is "3,1,2".
 *
 * The index of an TPS element shows the position of this element in the TPS vector. The index starts from 0.
 * Whence the dimension and the highest order are given, the relation between the index and the orders is
 * determined, which is not related to the value of a specific TPS vector.
 *
 * The purpose of this table is to provide a method to quickly find the orders using the index and vice versa.
 */
class ADOrderTable{
    std::vector<std::vector<int>> order_table; ///< Used to find the orders by the index.
    std::map<std::vector<int>, int> order_index; ///< Used to find the index by the orders.
    bool valid = false; ///< Shows whether this table exists. Default value is false.
public :
    void generate_order_table();    //Create the ad_order_table.
    void clear_order_table();   //Delete the existing ad_order_table.
    std::vector<std::vector<int>>::iterator table_begin(){return order_table.begin();}
    std::vector<std::vector<int>>::iterator table_end(){return order_table.end();}
    std::vector<int>& orders(int i) {return order_table.at(i);}  //Find the orders of an element by its index
    bool valid_table(){return valid;}  ///<Check if the ad_order_table exist.
    /** \brief Given the orders of an element, returns its index.
     * \return Index.
     */
    int find_index(std::vector<int>& orders){return order_index.at(orders);}
};

////******************** Additional Methods for TSP Vectors ************************////
//Create the ad_order_table that shows the relation between the index and the orders of an element in a TPS vector.
void ad_generate_order_table();
bool ad_valid_order_table(); // Check if the ad_order_table exists.
std::vector<int>& ad_element_orders(int i); //Return the orders of an element given its index.

unsigned int ad_dim(); //Return the TPS base number.
void ad_reset_vector(const TVEC iv); //Reset all the elements to zero, still keep the length of the vector.
int ad_change_order(unsigned int new_order);//temporarily lower the TPS order.
void ad_restore_order();//Restore the original TPS order, which is larger than the current one
void ad_reserve(const unsigned int n);  //Reserve memory for n TPS vectors.
void ad_clear(); //Destroy the TPS environment and release memory.
void ad_assign(unsigned int &i);    //Assign memory to a TPS vector. The length of the vector is zero.
void ad_copy(const SymEngine::Expression* isrc, int length, const TVEC* idst); //Copy memory to a TPS vector.
SymEngine::Expression ad_con(const TVEC iv); //Return the constant part of the TPS vector
void ad_reset_const(const TVEC iv, SymEngine::Expression x); //Reset the TPS vector constant element as x and all other elements zero
unsigned int ad_remain();       //Space (number) available for new TPS vectors.
unsigned int ad_count();        //Number of TPS vectors allocated.
void ad_mult_c(const TVEC iv, double c, TVEC ov); //Multiple the TPS vector iv with a constant number c, result stored in ov.
void ad_mult_c(const TVEC iv, SymEngine::Expression c, TVEC ov);
void ad_mult_const(const TVEC* iv, SymEngine::Expression* c);
void ad_mult_const(const TVEC* iv, double* c);
void ad_div_c(const TVEC* iv, const SymEngine::Expression* c);
void ad_div_c(const TVEC* iv, const double* c);
void ad_c_div(const TVEC* iv, const SymEngine::Expression* c, TVEC* ivret);
void ad_c_div(const TVEC* iv, const double* c, TVEC* ivret);
void ad_add_const(const TVEC i, double r, TVEC o);
void ad_add_const(const TVEC i, SymEngine::Expression r, TVEC o);
void ad_add_const(const TVEC* i, double *r);
void ad_add_const(const TVEC* i, SymEngine::Expression *r);
    
void ad_substitute_const(const TVEC iv, unsigned int base_id, double x, TVEC ov);
void ad_substitute(const TVEC iv, unsigned int base_id, const TVEC v, TVEC ov);
void ad_substitute(const TVEC iv, std::vector<unsigned int> &base_id, std::vector<TVEC> &v, TVEC ov);
void ad_substitute(std::vector<TVEC> &ivecs, std::vector<unsigned int> &base_id, std::vector<TVEC> &v, std::vector<TVEC> &ovecs) ;
void ad_composition(std::vector<TVEC> &ivecs, std::vector<TVEC> &v, std::vector<TVEC> &ovecs);
void ad_composition(std::vector<TVEC> &ivecs, std::vector<double> &v, std::vector<SymEngine::Expression> &ovecs);
// void ad_composition(std::vector<TVEC> &ivecs, std::vector<std::complex<double> > &v, std::vector<std::complex<double> > &ovecs);
void ad_add(const unsigned int idst, const unsigned int jsrc, unsigned int ov);
void ad_sub(const unsigned int idst, const unsigned int jsrc, TVEC ov);
void ad_add_const(const TVEC i, double r, TVEC ov);
SymEngine::Expression ad_elem(const TVEC &vec, std::vector<int> &idx);
SymEngine::Expression ad_derivative(const TVEC &vec, std::vector<int> &idx) ;
void ad_elem(const TVEC &vec, unsigned int idx, std::vector<unsigned int>& c, SymEngine::Expression& x);
void ad_derivative(const TVEC &vec, unsigned int idx, unsigned int* c, SymEngine::Expression& x);
void ad_derivative(const TVEC &vec, unsigned int idx, std::vector<unsigned int>& c, SymEngine::Expression& x);
void ad_pok(const TVEC &vec, std::vector<int> &idx, double x);
void ad_pok(const TVEC &vec, std::vector<int> &idx, SymEngine::Expression x);
void ad_pok(const TVEC &vec, int k, SymEngine::Expression expr);
int ad_order(); //Return the order of the TPS environment.
void ad_clean(const TVEC &iv, const double eps); //Set the coefficients smaller than eps to zero.
int ad_full_length();   //Return the maximum length of a TPS.
void ad_int(TVEC iv, unsigned int base_id, TVEC ov); //Integrate w.r.t. the specific base.
int ad_n_element(TVEC v);   //Number of non-zero element!
bool ad_zero_check(TVEC v, double eps = -1); //Check if all the abs value of the coefficients in v are zero or smaller than a given eps.
// double ad_norm(TVEC v); //Norm of the TPS vector.
// double ad_weighted_norm(TVEC v, double w); //Weighted norm of the TPS vector.
unsigned int ad_last_note();    //Index of the last available slot in the TPS vector pool.
unsigned int ad_next_note();    //Index of the next available slot in the TPS vector pool.
void print_vec(unsigned int ii, std::ostream& os);
void print_vec(unsigned int ii, unsigned int jj, std::ostream& os);
} //namespace SymbTPSA
#endif // SYMBTPSA_EXTEND

