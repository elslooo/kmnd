/*
 * Copyright (C) 2015-11-02, Tim van Elsloo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <gtest/gtest.h>

#include "../../src/option.h"

#include "malloc.h"

TEST(OptionUint8Fixture, NameDescriptionFlags) {
    KMND_MEM_LEAK_PRE();

    /* Create a new uint8 option. */
    kmnd_t *uint8 = kmnd_uint8_new('i', "uint8", "This is a uint8.",
                                   KMND_FLAGS_REQUIRED, 0);

    kmnd_option_t *option = (kmnd_option_t *) uint8;

    /* Make sure that the character, name and description are correctly set. */
    EXPECT_EQ('i', option->character);
    EXPECT_STREQ("uint8", option->core.name);
    EXPECT_STREQ("This is a uint8.", option->core.description);
    EXPECT_EQ(KMND_FLAGS_REQUIRED, option->flags);

    /* Free the option. */
    kmnd_free(uint8);

    KMND_MEM_LEAK_POST();
}

TEST(OptionUint8Fixture, DefaultValue) {
    KMND_MEM_LEAK_PRE();

    /* Create a new uint8 option. */
    kmnd_t *uint8 = kmnd_uint8_new('i', "uint8", "This is a uint8.",
                                   KMND_FLAGS_REQUIRED, 7);

    kmnd_option_t *option = (kmnd_option_t *) uint8;

    /* Make sure that the value is correctly set. */
    EXPECT_EQ(7, kmnd_uint8_get(uint8, NULL));

    /* Free the option. */
    kmnd_free(uint8);

    KMND_MEM_LEAK_POST();
}

TEST(OptionUint8Fixture, ParseMin) {
    KMND_MEM_LEAK_PRE();

    /* Create a new uint8 option. */
    kmnd_t *uint8 = kmnd_uint8_new('i', "uint8", "This is a uint8.",
                                   KMND_FLAGS_REQUIRED, 7);

    kmnd_option_t *option = (kmnd_option_t *) uint8;
    kmnd_option_activate((kmnd_t *) option, option, "0");

    /* Make sure that the value is correctly set. */
    EXPECT_EQ(0, kmnd_uint8_get(uint8, NULL));

    /* Free the option. */
    kmnd_free(uint8);

    KMND_MEM_LEAK_POST();
}

TEST(OptionUint8Fixture, ParseMax) {
    KMND_MEM_LEAK_PRE();

    /* Create a new uint8 option. */
    kmnd_t *uint8 = kmnd_uint8_new('i', "uint8", "This is a uint8.",
                                   KMND_FLAGS_REQUIRED, 7);

    kmnd_option_t *option = (kmnd_option_t *) uint8;
    kmnd_option_activate((kmnd_t *) option, option, "255");

    /* Make sure that the value is correctly set. */
    EXPECT_EQ(255, kmnd_uint8_get(uint8, NULL));

    /* Free the option. */
    kmnd_free(uint8);

    KMND_MEM_LEAK_POST();
}

TEST(OptionUint8Fixture, ParseUnderflow) {
    EXPECT_DEATH({
        /* Create a new uint8 option. */
        kmnd_t *kmnd = kmnd_new(NULL, NULL, NULL, NULL);
        kmnd_fd(kmnd, STDERR_FILENO);

        kmnd_t *uint8 = kmnd_uint8_new('i', "uint8", "This is a uint8.",
                                       KMND_FLAGS_REQUIRED, 7);

        kmnd_option_t *option = (kmnd_option_t *) uint8;

        EXPECT_EQ(-1, kmnd_option_activate(kmnd, option, "-1"));

        /* Free the option. */
        kmnd_free(uint8);

        exit(1);
    }, "Invalid value");
}

TEST(OptionUint8Fixture, ParseOverflow) {
    EXPECT_DEATH({
        /* Create a new uint8 option. */
        kmnd_t *kmnd = kmnd_new(NULL, NULL, NULL, NULL);
        kmnd_fd(kmnd, STDERR_FILENO);

        kmnd_t *uint8 = kmnd_uint8_new('i', "uint8", "This is a uint8.",
                                       KMND_FLAGS_REQUIRED, 7);

        kmnd_option_t *option = (kmnd_option_t *) uint8;

        EXPECT_EQ(-1, kmnd_option_activate(kmnd, option, "256"));

        /* Free the option. */
        kmnd_free(uint8);

        exit(1);
    }, "Invalid value");
}
