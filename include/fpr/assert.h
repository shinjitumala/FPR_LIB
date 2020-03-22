#pragma once

#include <experimental/source_location>
#include <iostream>
#include <string>

#include <fpr/log.h>
#include <fpr/log/ansicc.h>

namespace fpr {
/**
 * If cond is false, location is printed then action() is executed.
 * After which, cerr is flushed and ::abort() is called.
 * @param cond 
 * @param cond_str 
 * @param action 
 * @param location 
 */
void my_assert(
    bool cond,
    const string cond_str,
    function<void()> action = []() {},
    experimental::source_location location =
        experimental::source_location::current());

/**
 * If cond is false, location is printed then action() is executed.
 * After which, cerr is flushed.
 * @param cond 
 * @param cond_str 
 * @param action 
 * @param location 
 */
void my_warn(
    bool cond,
    const string cond_str,
    function<void()> action = []() {},
    experimental::source_location location =
        experimental::source_location::current());

/**
 * Print location info to 'os'
 * @param loc 
 * @param os 
 */
void print_location(const experimental::source_location &loc, ostream &os);

/**
 * action() is called if condition is false.
 * @param condition 
 * @action Actions to take such as printing messages before executing crash()
 */
#ifndef NDEBUG
#define asrt(condition, action) fpr::my_assert(condition, #condition)
#else
#define asrt(condition, action)
#endif

/**
 * action() is called if condition is false.
 * @param condition 
 * @action Actions to take such as printing messages before executing crash()
 */
#ifndef NDEBUG
#define wsrt(condition, action) fpr::my_warn(condition, #condition)
#else
#define wsrt(condition, action)
#endif
} // namespace fpr
