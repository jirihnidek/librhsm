/*
 * It is possible to compile this example with something like this:
 * 
 * gcc -o example example.c -I../forks/librhsm -L../forks/librhsm_build/rhsm \
 *     -lrhsm -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include \
 *     -I/usr/include/json-glib-1.0 -lglib-2.0
 */

#include <rhsm/rhsm.h>
#include <stdio.h>
#include <stdlib.h>

#include <glib.h>
#include <glib/gprintf.h>

int main(void)
{
  RHSMContext *ctx = NULL;
  const gchar *arch = NULL;
  const gchar *prod_cert_dir = NULL;
  const gchar *ent_dir = NULL;
  const gchar *conf_file = NULL;
  const gchar *base_url = NULL;
  GKeyFile *repo_file = NULL;
  const gchar *repo_file_content = NULL;
  gsize length;
  GError *error;

  /* Get RHSM context */
  ctx = rhsm_context_new();

  /* Try to get architecture of the system */
  arch = rhsm_context_get_arch(ctx);
  printf("architexture: %s\n", arch);

  /* Try to get entitlement directory */
  ent_dir = rhsm_context_get_entitlement_cert_dir(ctx);
  printf("entitlement certificate directory: %s\n", ent_dir);

  /* Try to get product certificate directory */
  prod_cert_dir = rhsm_context_get_product_cert_dir(ctx);
  printf("product certificate directory: %s\n", prod_cert_dir);

  /* Try to get configuration file */
  conf_file = rhsm_context_get_conf_file(ctx);
  printf("configuration file: %s\n", conf_file);

  base_url = rhsm_context_get_baseurl(ctx);
  printf("base URL: %s\n", base_url);

  //rhsm_context_get_entitlement_certificates(ctx);

  repo_file = rhsm_utils_yum_repo_from_context(ctx);
  repo_file_content = g_key_file_to_data(repo_file, &length, &error);
  printf("content of repo file:\n%s\n", repo_file_content);


  free(ctx);
  return EXIT_SUCCESS;
}
