#define MYSQL_SERVER

#include <sql_parse.h>
#include <sql_select.h>
#include <sql_table.h>

#ifdef __cplusplus
extern "C" {
#endif

my_bool remote_sql_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
void remote_sql_deinit(UDF_INIT *initid);
long long remote_sql(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

#ifdef __cplusplus
}
#endif

my_bool remote_sql_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
    if (args->arg_count == 1 &&
        args->arg_type[0] == STRING_RESULT) {
        return 0;
    } else {
        return 1;
    }
}

void remote_sql_deinit(UDF_INIT *initid)
{
}

long long remote_sql(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
    THD *thd = current_thd;

    if(write_bin_log(thd, TRUE, args->args[0], *args->lengths)) {
        return -1;
    }

    return 0;
}

