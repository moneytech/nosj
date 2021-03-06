/***************************************************************************//**

  @file         parse_atomics.c

  @author       Stephen Brennan

  @date         Created Wednesday, 25 November 2015

  @brief        Tests for parsing true, false, null.

  @copyright    Copyright (c) 2015, Stephen Brennan.  Released under the Revised
                BSD License.  See LICENSE.txt for details.

*******************************************************************************/

#include "libstephen/ut.h"
#include "nosj.h"
#include "tests.h"

static int test_parse_true(void)
{
  wchar_t input[] = L"true";
  struct json_token tokens[1];
  struct json_parser p = json_parse(input, tokens, 1);
  TEST_ASSERT(p.error == JSONERR_NO_ERROR);
  TEST_ASSERT(p.tokenidx == 1);
  TEST_ASSERT(p.textidx == sizeof(input)/sizeof(wchar_t) - 1);
  TEST_ASSERT(tokens[0].type == JSON_TRUE);
  TEST_ASSERT(tokens[0].start == 0);
  TEST_ASSERT(tokens[0].end == 3);
  TEST_ASSERT(tokens[0].child == 0);
  TEST_ASSERT(tokens[0].next == 0);
  return 0;
}

static int test_parse_false(void)
{
  wchar_t input[] = L"false";
  struct json_token tokens[1];
  struct json_parser p = json_parse(input, tokens, 1);
  TEST_ASSERT(p.error == JSONERR_NO_ERROR);
  TEST_ASSERT(p.tokenidx == 1);
  TEST_ASSERT(p.textidx == sizeof(input)/sizeof(wchar_t) - 1);
  TEST_ASSERT(tokens[0].type == JSON_FALSE);
  TEST_ASSERT(tokens[0].start == 0);
  TEST_ASSERT(tokens[0].end == 4);
  TEST_ASSERT(tokens[0].child == 0);
  TEST_ASSERT(tokens[0].next == 0);
  return 0;
}

static int test_parse_null(void)
{
  wchar_t input[] = L"null";
  struct json_token tokens[1];
  struct json_parser p = json_parse(input, tokens, 1);
  TEST_ASSERT(p.error == JSONERR_NO_ERROR);
  TEST_ASSERT(p.tokenidx == 1);
  TEST_ASSERT(p.textidx == sizeof(input)/sizeof(wchar_t) - 1);
  TEST_ASSERT(tokens[0].type == JSON_NULL);
  TEST_ASSERT(tokens[0].start == 0);
  TEST_ASSERT(tokens[0].end == 3);
  TEST_ASSERT(tokens[0].child == 0);
  TEST_ASSERT(tokens[0].next == 0);
  return 0;
}

static int test_parse_empty_string(void)
{
  wchar_t input[] = L"";
  struct json_parser p = json_parse(input, NULL, 0);
  TEST_ASSERT(p.error == JSONERR_PREMATURE_EOF);
  return 0;
}

static int test_parse_whitespace_string(void)
{
  wchar_t input[] = L" \t\r\n";
  struct json_parser p = json_parse(input, NULL, 0);
  TEST_ASSERT(p.error == JSONERR_PREMATURE_EOF);
  return 0;
}

static int test_parse_invalid_true(void)
{
  wchar_t input[] = L"trua";
  struct json_parser p = json_parse(input, NULL, 0);
  TEST_ASSERT(p.error == JSONERR_UNEXPECTED_TOKEN);
  return 0;
}

static int test_parse_invalid_false(void)
{
  wchar_t input[] = L"flase";
  struct json_parser p = json_parse(input, NULL, 0);
  TEST_ASSERT(p.error == JSONERR_UNEXPECTED_TOKEN);
  return 0;
}

static int test_parse_invalid_null(void)
{
  wchar_t input[] = L"nulL";
  struct json_parser p = json_parse(input, NULL, 0);
  TEST_ASSERT(p.error == JSONERR_UNEXPECTED_TOKEN);
  return 0;
}

void test_parse_atomics(void)
{
  smb_ut_group *group = su_create_test_group("test/parse_atomics.c");

  smb_ut_test *parse_true = su_create_test("parse_true", test_parse_true);
  su_add_test(group, parse_true);

  smb_ut_test *parse_false = su_create_test("parse_false", test_parse_false);
  su_add_test(group, parse_false);

  smb_ut_test *parse_null = su_create_test("parse_null", test_parse_null);
  su_add_test(group, parse_null);

  smb_ut_test *parse_empty_string = su_create_test("parse_empty_string", test_parse_empty_string);
  su_add_test(group, parse_empty_string);

  smb_ut_test *parse_whitespace_string = su_create_test("parse_whitespace_string", test_parse_whitespace_string);
  su_add_test(group, parse_whitespace_string);

  smb_ut_test *parse_invalid_true = su_create_test("parse_invalid_true", test_parse_invalid_true);
  su_add_test(group, parse_invalid_true);

  smb_ut_test *parse_invalid_false = su_create_test("parse_invalid_false", test_parse_invalid_false);
  su_add_test(group, parse_invalid_false);

  smb_ut_test *parse_invalid_null = su_create_test("parse_invalid_null", test_parse_invalid_null);
  su_add_test(group, parse_invalid_null);

  su_run_group(group);
  su_delete_group(group);
}
