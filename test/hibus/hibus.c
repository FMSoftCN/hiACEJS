#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <linux/limits.h>
#include <hibus.h>
#include "jerryscript.h"
#include "jerryscript-ext/arg.h"
#include "hibus-common.h"

// data structure for hibus object
typedef struct
{
    char app_name[128];
    char runner_name[64];
    char path_socket[PATH_MAX];
    int fd_socket;
    hibus_conn * context;
} hibus_object_t;

// free object
static void hibus_free_object(void *native_p)
{
    if(native_p)
    {
        hibus_object_t * hibus_object = (hibus_object_t *)native_p;
        if(hibus_object->fd_socket != -1)
        {
            hibus_disconnect(hibus_object->context);
            hibus_object->fd_socket = -1;
            hibus_object->context = NULL;
        }
        free(native_p);
    }
    native_p = NULL;
}

// free resource when cleanup
static const jerry_object_native_info_t hibus_native_info =
{
    .free_cb = hibus_free_object,
};

// app_name getter
static jerry_value_t hibus_getter_appName (const jerry_value_t this_obj,
                                   const jerry_value_t func_obj,
                                   const jerry_value_t args[],
                                   const jerry_length_t argc)
{
    void * hibus_object = NULL;
    bool has_p = jerry_get_object_native_pointer (func_obj, &hibus_object, &hibus_native_info);
    if (!has_p)
        return jerry_create_undefined ();

    return jerry_create_string (((hibus_object_t *)hibus_object)->app_name);
}

// app_name setter
static jerry_value_t hibus_setter_appName (const jerry_value_t this_obj,
                                    const jerry_value_t func_obj,
                                    const jerry_value_t args[],
                                    const jerry_length_t argc)
{
    void * hibus_object = NULL;
    bool has_p = jerry_get_object_native_pointer (func_obj, &hibus_object, &hibus_native_info);
    if (!has_p)
        return jerry_create_boolean (false);

    memset(((hibus_object_t *)hibus_object)->app_name, 0, 128);
    jerry_string_to_char_buffer(args[0], ((hibus_object_t *)hibus_object)->app_name, 127);
    return jerry_create_boolean (true);
}

// runner_name getter
static jerry_value_t hibus_getter_runnerName (const jerry_value_t this_obj,
                                   const jerry_value_t func_obj,
                                   const jerry_value_t args[],
                                   const jerry_length_t argc)
{
    void * hibus_object = NULL;
    bool has_p = jerry_get_object_native_pointer (func_obj, &hibus_object, &hibus_native_info);
    if (!has_p)
        return jerry_create_undefined ();

    return jerry_create_string (((hibus_object_t *)hibus_object)->runner_name);
}

// runner_name setter
static jerry_value_t hibus_setter_runnerName (const jerry_value_t this_obj,
                                    const jerry_value_t func_obj,
                                    const jerry_value_t args[],
                                    const jerry_length_t argc)
{
    void * hibus_object = NULL;
    bool has_p = jerry_get_object_native_pointer (func_obj, &hibus_object, &hibus_native_info);
    if (!has_p)
        return jerry_create_boolean (false);

    memset(((hibus_object_t *)hibus_object)->runner_name, 0, 64);
    jerry_string_to_char_buffer(args[0], ((hibus_object_t *)hibus_object)->runner_name, 63);
    return jerry_create_boolean (true);
}

// path_socket getter
static jerry_value_t hibus_getter_pathSocket (const jerry_value_t this_obj,
                                   const jerry_value_t func_obj,
                                   const jerry_value_t args[],
                                   const jerry_length_t argc)
{
    void * hibus_object = NULL;
    bool has_p = jerry_get_object_native_pointer (func_obj, &hibus_object, &hibus_native_info);
    if (!has_p)
        return jerry_create_undefined ();

    return jerry_create_string (((hibus_object_t *)hibus_object)->path_socket);
}

// path_socket setter
static jerry_value_t hibus_setter_pathSocket (const jerry_value_t this_obj,
                                    const jerry_value_t func_obj,
                                    const jerry_value_t args[],
                                    const jerry_length_t argc)
{
    void * hibus_object = NULL;
    bool has_p = jerry_get_object_native_pointer (func_obj, &hibus_object, &hibus_native_info);
    if (!has_p)
        return jerry_create_boolean (false);

    memset(((hibus_object_t *)hibus_object)->path_socket, 0, PATH_MAX);
    jerry_string_to_char_buffer(args[0], ((hibus_object_t *)hibus_object)->path_socket, PATH_MAX - 1);
    return jerry_create_boolean (true);
}

// status getter
static jerry_value_t hibus_getter_status (const jerry_value_t this_obj,
                                   const jerry_value_t func_obj,
                                   const jerry_value_t args[],
                                   const jerry_length_t argc)
{
    void * hibus_object = NULL;
    bool has_p = jerry_get_object_native_pointer (func_obj, &hibus_object, &hibus_native_info);
    if (!has_p)
        return jerry_create_boolean (false);

    if(((hibus_object_t *)hibus_object)->fd_socket == -1)
        return jerry_create_boolean (false);
    else
        return jerry_create_boolean (true);
    return jerry_create_boolean (false);
}

// for functions: connect
static jerry_value_t connect_handler (const jerry_value_t this_obj,
                                    const jerry_value_t func_obj,
                                    const jerry_value_t args[],
                                    const jerry_length_t argc)
{
    void * hibus_object = NULL;
    bool has_p = jerry_get_object_native_pointer (func_obj, &hibus_object, &hibus_native_info);
    if (!has_p)
        return jerry_create_boolean (false);

    if (((hibus_object_t *)hibus_object)->fd_socket != -1)
    {
        hibus_disconnect(((hibus_object_t *)hibus_object)->context);
        ((hibus_object_t *)hibus_object)->fd_socket = -1;
        ((hibus_object_t *)hibus_object)->context = NULL;
    }

    memset(((hibus_object_t *)hibus_object)->app_name, 0, 128);
    memset(((hibus_object_t *)hibus_object)->runner_name, 0, 64);
    memset(((hibus_object_t *)hibus_object)->path_socket, 0, PATH_MAX);
    jerry_string_to_char_buffer(args[0], ((hibus_object_t *)hibus_object)->app_name, 127);
    jerry_string_to_char_buffer(args[1], ((hibus_object_t *)hibus_object)->runner_name, 63);
    jerry_string_to_char_buffer(args[2], ((hibus_object_t *)hibus_object)->path_socket, PATH_MAX - 1);

    ((hibus_object_t *)hibus_object)->fd_socket = hibus_connect_via_unix_socket (((hibus_object_t *)hibus_object)->path_socket, \
                ((hibus_object_t *)hibus_object)->app_name, ((hibus_object_t *)hibus_object)->runner_name, \
                &(((hibus_object_t *)hibus_object)->context));

    printf("create object: app_name = %s, runner_name = %s, path_socket = %s, fd = %d, conn = %p\n", \
            ((hibus_object_t *)hibus_object)->app_name, ((hibus_object_t *)hibus_object)->runner_name, \
            ((hibus_object_t *)hibus_object)->path_socket, ((hibus_object_t *)hibus_object)->fd_socket, \
            ((hibus_object_t *)hibus_object)->context);
    if (((hibus_object_t *)hibus_object)->fd_socket != -1)
        return jerry_create_boolean (true);
    else
        return jerry_create_boolean (false);

    return jerry_create_boolean (false);
}

// for functions: disconnect
static jerry_value_t disconnect_handler (const jerry_value_t this_obj,
                                    const jerry_value_t func_obj,
                                    const jerry_value_t args[],
                                    const jerry_length_t argc)
{
    void * hibus_object = NULL;
    bool has_p = jerry_get_object_native_pointer (func_obj, &hibus_object, &hibus_native_info);
    if (!has_p)
        return jerry_create_boolean (false);

printf("printinfo: disconnect\n");
    if (((hibus_object_t *)hibus_object)->fd_socket != -1)
    {
        hibus_disconnect(((hibus_object_t *)hibus_object)->context);
        ((hibus_object_t *)hibus_object)->fd_socket = -1;
        ((hibus_object_t *)hibus_object)->context = NULL;
    }
    return jerry_create_boolean (true);
}

// for function: send
static jerry_value_t send_handler (const jerry_value_t this_obj,
                                    const jerry_value_t func_obj,
                                    const jerry_value_t args[],
                                    const jerry_length_t argc)
{
    int length = -1;
    char content[4096];
    void * hibus_object = NULL;
    bool has_p = jerry_get_object_native_pointer (func_obj, &hibus_object, &hibus_native_info);
    if (!has_p)
        return  jerry_create_number (-1);

    memset(content, 0, 4096);
    jerry_string_to_char_buffer(args[0], content, 4096);
    length = jerry_get_number_value(args[1]);

printf("printinfo: send %d bytes: %s\n", length, content);
    if (((hibus_object_t *)hibus_object)->fd_socket != -1 && ((hibus_object_t *)hibus_object)->context)
    {
        length = hibus_send_text_packet (((hibus_object_t *)hibus_object)->context, content, length);
    }

    return  jerry_create_number (length);
}

// for function: read 
static jerry_value_t read_handler (const jerry_value_t this_obj,
                                    const jerry_value_t func_obj,
                                    const jerry_value_t args[],
                                    const jerry_length_t argc)
{
    unsigned int length = 4096;
    unsigned char content[4096];
    int timeout = 0;
    void * hibus_object = NULL;
    bool has_p = jerry_get_object_native_pointer (func_obj, &hibus_object, &hibus_native_info);
    if (!has_p)
        return jerry_create_undefined ();

    timeout = jerry_get_number_value(args[0]);
    memset(content, 0, 4096);

//    sprintf(content, "{\"abcd\":123456, \"xyz\":890}");
//    length = strlen((char *)content);

    if (((hibus_object_t *)hibus_object)->fd_socket != -1 && ((hibus_object_t *)hibus_object)->context)
    {
        fd_set rfds;
        struct timeval tv;
        int result = 0;
        int maxfd = 0;

        FD_ZERO(&rfds);
        FD_SET(((hibus_object_t *)hibus_object)->fd_socket, &rfds);
        maxfd = ((hibus_object_t *)hibus_object)->fd_socket + 1;

        tv.tv_sec = timeout / 1000;
        tv.tv_usec = (timeout % 1000) * 1000;

        result = select(maxfd, &rfds, NULL, NULL, &tv);
        if(result > 0)
        {
            length = hibus_read_packet (((hibus_object_t *)hibus_object)->context, (void *) content, &length);
        }
    }

    if(length)
        return jerry_create_string ((const jerry_char_t *) content);

    return jerry_create_undefined ();
}

// Register a JavaScript function in the global object.
static void register_js_function (const char *name_p,                    // name of the function
                                  jerry_external_handler_t handler_p)    // function callback
{
    jerry_value_t global_obj_val = jerry_get_global_object ();

    jerry_value_t function_val = jerry_create_external_function (handler_p);
    jerry_value_t function_name_val = jerry_create_string ((const jerry_char_t *) name_p);
    jerry_value_t result_val = jerry_set_property (global_obj_val, function_name_val, function_val);

    if (jerry_value_is_error (result_val)) 
        printf ("Error: Failed to add the %s property\n", name_p);

    jerry_release_value (function_name_val);
    jerry_release_value (function_val);
    jerry_release_value (global_obj_val);

    jerry_release_value (result_val);
}

static jerry_value_t create_object_hibus_handler (const jerry_value_t function_object,
                                    const jerry_value_t function_this,
                                    const jerry_value_t arguments[],
                                    const jerry_length_t arguments_count)
{
    JERRY_UNUSED (function_object);
    JERRY_UNUSED (arguments);
    JERRY_UNUSED (arguments_count);
    TEST_ASSERT (jerry_value_is_object (function_this));

    // create HiBus object
    hibus_object_t * hibus_object = malloc(sizeof(hibus_object_t));
    if(hibus_object == NULL)
        return jerry_create_undefined ();
    memset((void *)hibus_object, 0, sizeof(hibus_object_t));
    hibus_object->fd_socket = -1;

    // check param
    if(arguments_count < 2)
        return jerry_create_boolean (false);

    // set getter and setter function for app_name  
    jerry_property_descriptor_t prop_desc;
    jerry_init_property_descriptor_fields (&prop_desc);
    prop_desc.is_get_defined = true;
    prop_desc.getter = jerry_create_external_function (hibus_getter_appName);
    prop_desc.is_set_defined = true;
    prop_desc.setter = jerry_create_external_function (hibus_setter_appName);

    jerry_value_t prop_name = jerry_create_string ((const jerry_char_t *) "appName");
    jerry_value_t return_value = jerry_define_own_property (function_this, prop_name, &prop_desc);
    if (jerry_value_is_error (return_value))
        printf("app_name attribution: setter and getter error\n");
    jerry_release_value (return_value);
    jerry_release_value (prop_name);
    jerry_free_property_descriptor_fields (&prop_desc);

    // set getter and setter function for runner_name  
    jerry_init_property_descriptor_fields (&prop_desc);
    prop_desc.is_get_defined = true;
    prop_desc.getter = jerry_create_external_function (hibus_getter_runnerName);
    prop_desc.is_set_defined = true;
    prop_desc.setter = jerry_create_external_function (hibus_setter_runnerName);

    prop_name = jerry_create_string ((const jerry_char_t *) "runnerName");
    return_value = jerry_define_own_property (function_this, prop_name, &prop_desc);
    if (jerry_value_is_error (return_value))
        printf("runner_name attribution: setter and getter error\n");
    jerry_release_value (return_value);
    jerry_release_value (prop_name);
    jerry_free_property_descriptor_fields (&prop_desc);

    // set getter and setter function for path_socket
    jerry_init_property_descriptor_fields (&prop_desc);
    prop_desc.is_get_defined = true;
    prop_desc.getter = jerry_create_external_function (hibus_getter_pathSocket);
    prop_desc.is_set_defined = true;
    prop_desc.setter = jerry_create_external_function (hibus_setter_pathSocket);

    prop_name = jerry_create_string ((const jerry_char_t *) "pathSocket");
    return_value = jerry_define_own_property (function_this, prop_name, &prop_desc);
    if (jerry_value_is_error (return_value))
        printf("path_socket attribution: setter and getter error\n");
    jerry_release_value (return_value);
    jerry_release_value (prop_name);
    jerry_free_property_descriptor_fields (&prop_desc);

    // set getter and setter function for isConnect 
    jerry_init_property_descriptor_fields (&prop_desc);
    prop_desc.is_get_defined = true;
    prop_desc.getter = jerry_create_external_function (hibus_getter_status);
    prop_desc.is_set_defined = false;

    prop_name = jerry_create_string ((const jerry_char_t *) "status");
    return_value = jerry_define_own_property (function_this, prop_name, &prop_desc);
    if (jerry_value_is_error (return_value))
        printf("status attribution: getter error\n");
    jerry_release_value (return_value);
    jerry_release_value (prop_name);
    jerry_free_property_descriptor_fields (&prop_desc);

    // add functions
    // connect
    jerry_value_t func_obj = jerry_create_external_function (connect_handler);
    jerry_value_t func_name = jerry_create_string ((const jerry_char_t *) "connect");
    jerry_release_value (jerry_set_property (function_this, func_name, func_obj));
    jerry_release_value (func_obj);
    jerry_release_value (func_name);

    // disconnect
    func_obj = jerry_create_external_function (disconnect_handler);
    func_name = jerry_create_string ((const jerry_char_t *) "disconnect");
    jerry_release_value (jerry_set_property (function_this, func_name, func_obj));
    jerry_release_value (func_obj);
    jerry_release_value (func_name);

    // send 
    func_obj = jerry_create_external_function (send_handler);
    func_name = jerry_create_string ((const jerry_char_t *) "send");
    jerry_release_value (jerry_set_property (function_this, func_name, func_obj));
    jerry_release_value (func_obj);
    jerry_release_value (func_name);

    // read 
    func_obj = jerry_create_external_function (read_handler);
    func_name = jerry_create_string ((const jerry_char_t *) "read");
    jerry_release_value (jerry_set_property (function_this, func_name, func_obj));
    jerry_release_value (func_obj);
    jerry_release_value (func_name);

    // set free function
    jerry_set_object_native_pointer (function_this, hibus_object, &hibus_native_info);

    memset(((hibus_object_t *)hibus_object)->app_name, 0, 128);
    memset(((hibus_object_t *)hibus_object)->runner_name, 0, 64);
    memset(((hibus_object_t *)hibus_object)->path_socket, 0, PATH_MAX);

    // construction
    switch(arguments_count)
    {
        case 0:
        case 1:
        case 2:
            jerry_string_to_char_buffer(arguments[0], hibus_object->app_name, 127);
            jerry_string_to_char_buffer(arguments[1], hibus_object->runner_name, 63);
            sprintf(hibus_object->path_socket, "/var/tmp/hibus.sock");
            break;
        default:
            jerry_string_to_char_buffer(arguments[0], hibus_object->app_name, 127);
            jerry_string_to_char_buffer(arguments[1], hibus_object->runner_name, 63);
            jerry_string_to_char_buffer(arguments[2], hibus_object->path_socket, PATH_MAX - 1);
            break;
    }

    // connect to hibus
    hibus_object->fd_socket = hibus_connect_via_unix_socket (hibus_object->path_socket, \
            hibus_object->app_name, hibus_object->runner_name, &(hibus_object->context));
    printf("create object: app_name = %s, runner_name = %s, path_socket = %s, fd = %d, conn = %p\n", \
            hibus_object->app_name, hibus_object->runner_name, hibus_object->path_socket, hibus_object->fd_socket, hibus_object->context);
    return jerry_create_boolean (true);

}

static jerry_value_t printf_handler (const jerry_value_t function_object,
                                    const jerry_value_t function_this,
                                    const jerry_value_t arguments[],
                                    const jerry_length_t arguments_count)
{
    char buffer[4096];
    memset(buffer, 0, 4096);
    jerry_string_to_char_buffer(arguments[0], buffer, 4096);

    printf("printinfo: %s\n", buffer);
}

int main (void)
{
    // const jerry_char_t script[] = "var a = new HiBusConn('cn.fmsoft.appagent', 'target0'); if (a.status) printinfo('true'); \
    //                               else printinfo('false'); a.connect('cn.fmsoft.sysmgr', 'target1'); var ss = \"abc\ndefg\"; \
    //                               a.send(ss, ss.length);";
    // const jerry_length_t script_size = sizeof (script) - 1;

    jerry_char_t script[4096];
    jerry_length_t script_size = 0;
    FILE * fp = NULL;

    memset(script, 0, 4096);
    if((fp = fopen("./HiBusConn.js","r")) == NULL)
    {
        perror("fail to read");
        exit (1) ;
    }
    script_size = fread(script, 1, 4096, fp);
    fclose(fp);

    // step 1: Initialize engine
    jerry_init (JERRY_INIT_EMPTY);

    // step 2: add the constructed function of my type
    register_js_function ("HiBusConn", create_object_hibus_handler);
    // only for test
    register_js_function ("printinfo", printf_handler);

    /* Setup Global scope code */
    jerry_value_t parsed_code = jerry_parse (NULL, 0, script, script_size, JERRY_PARSE_NO_OPTS);

    if (!jerry_value_is_error (parsed_code))
    {
        /* Execute the parsed source code in the Global scope */
        jerry_value_t ret_value = jerry_run (parsed_code);

        if (jerry_value_is_error (ret_value))
            printf("JavaScript running error!\n");

        /* Returned value must be freed */
        jerry_release_value (ret_value);
    }

    /* Parsed source code must be freed */
    jerry_release_value (parsed_code);

    /* Cleanup engine */
    jerry_cleanup ();

    return 0;
}
