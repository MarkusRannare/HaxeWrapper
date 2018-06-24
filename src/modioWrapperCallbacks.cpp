#include "modioWrapperCallbacks.h"

u32 current_function = 0;
std::map<int, value*> functions_stored;
value download_listener = NULL;

void onEmailRequest(void *object, ModioResponse response)
{
    int function_number = *((int*)object);
    value ret = val_call1(*(functions_stored[function_number]), alloc_int(response.code));
}

void onExchange(void *object, ModioResponse response)
{
    int function_number = *((int*)object);        
    value ret = val_call1(*(functions_stored[function_number]), alloc_int(response.code));
}

void onModsGet(void* object, ModioResponse response, ModioMod* mods, u32 mods_size)
{
    int function_number = *((int*)object);

    value mods_haxe = alloc_array (mods_size);
    for (int i = 0; i < mods_size; i++)
    {
        value mod = alloc_empty_object();
        alloc_field(mod,val_id("id"),alloc_int(mods[i].id));
        alloc_field(mod,val_id("name"),alloc_string(mods[i].name));
        alloc_field(mod,val_id("description"),alloc_string(mods[i].description));
        
        val_array_set_i (mods_haxe, i, mod);
    }
    value ret = val_call2(*(functions_stored[function_number]), mods_haxe, alloc_int(response.code));
}

void onModSubscribed(void* object, ModioResponse response, ModioMod mod)
{
    int function_number = *((int*)object);
    value ret = val_call1(*(functions_stored[function_number]), alloc_int(response.code));
}

void onModUnsubscribed(void* object, ModioResponse response)
{
    int function_number = *((int*)object);
    value ret = val_call1(*(functions_stored[function_number]), alloc_int(response.code));
}

void onModDownload(u32 response_code, u32 mod_id)
{
    if(download_listener != NULL)
    {
        val_check_function(download_listener, 1);
        value ret = val_call2(download_listener, alloc_int(response_code), alloc_int(mod_id));
    }
}

void onModAdded(void* object, ModioResponse response, ModioMod mod)
{
    int function_number = *((int*)object);
    value ret = val_call1(*(functions_stored[function_number]), alloc_int(response.code));
}

void onModEdited(void* object, ModioResponse response, ModioMod mod)
{
    int function_number = *((int*)object);
    value ret = val_call1(*(functions_stored[function_number]), alloc_int(response.code));
}