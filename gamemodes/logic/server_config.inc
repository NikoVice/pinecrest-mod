// ============================================================================
//  server_config.inc - Smart multi-server configuration loader (.env)
// ----------------------------------------------------------------------------
//  Reads "scriptfiles/.env" (KEY=VALUE format) at startup so the same gamemode
//  can run on several servers (different DB / hostname / port / id) without
//  editing the .pwn source. If the file is missing or a key is absent, the
//  hardcoded defaults below are used, so old behaviour is fully preserved.
//
//  NOTE: comments here are intentionally ASCII-only to stay safe under the
//  cp1251 encoding used by the rest of the source tree.
// ============================================================================

#if !defined _server_config_included
#define _server_config_included

// --- Configuration values (filled with safe defaults, overridden by .env) ---
new ENV_MYSQL_HOST[64]       = "127.0.0.1";
new ENV_MYSQL_USER[64]       = "pinecrestphp";
new ENV_MYSQL_PASS[64]       = "Ghrf88ls!!";
new ENV_MYSQL_DB[64]         = "pinecrestphp";

new ENV_SERVER_NAME[64]      = "Pinecrest RolePlay"; // browser hostname + gamemode text
new ENV_SERVER_ID            = -1;                   // -1 = auto-detect from port

stock Env_ApplyValue(const key[], const value[])
{
    if(!strcmp(key, "MYSQL_HOST", true))        format(ENV_MYSQL_HOST, sizeof(ENV_MYSQL_HOST), "%s", value);
    else if(!strcmp(key, "MYSQL_USER", true))   format(ENV_MYSQL_USER, sizeof(ENV_MYSQL_USER), "%s", value);
    else if(!strcmp(key, "MYSQL_PASSWORD", true)) format(ENV_MYSQL_PASS, sizeof(ENV_MYSQL_PASS), "%s", value);
    else if(!strcmp(key, "MYSQL_DATABASE", true)) format(ENV_MYSQL_DB, sizeof(ENV_MYSQL_DB), "%s", value);
    else if(!strcmp(key, "SERVER_NAME", true))  format(ENV_SERVER_NAME, sizeof(ENV_SERVER_NAME), "%s", value);
    else if(!strcmp(key, "SERVER_ID", true))    ENV_SERVER_ID = strval(value);
    return 1;
}

stock Env_ParseLine(line[])
{
    // strip trailing CR / LF / spaces / tabs
    new len = strlen(line);
    while(len > 0 && (line[len-1] == '\n' || line[len-1] == '\r' || line[len-1] == ' ' || line[len-1] == '\t'))
        line[--len] = EOS;

    // find first significant char (skip leading spaces / tabs)
    new start = 0;
    while(line[start] == ' ' || line[start] == '\t') start++;
    if(line[start] == EOS || line[start] == '#') return 0; // empty line or comment

    // locate '='
    new eq = -1;
    for(new i = start; line[i] != EOS; i++)
        if(line[i] == '=') { eq = i; break; }
    if(eq == -1) return 0; // no key/value pair

    new key[64], value[128];

    // key = [start .. eq)
    strmid(key, line, start, eq, sizeof(key));
    new klen = strlen(key);
    while(klen > 0 && (key[klen-1] == ' ' || key[klen-1] == '\t')) key[--klen] = EOS;

    // value = (eq .. len), skip spaces after '='
    new vstart = eq + 1;
    while(line[vstart] == ' ' || line[vstart] == '\t') vstart++;
    strmid(value, line, vstart, len, sizeof(value));

    // strip a single pair of surrounding quotes
    new vlen = strlen(value);
    if(vlen >= 2 && ((value[0] == '"' && value[vlen-1] == '"') || (value[0] == '\'' && value[vlen-1] == '\'')))
    {
        strdel(value, vlen-1, vlen);
        strdel(value, 0, 1);
    }

    Env_ApplyValue(key, value);
    return 1;
}

// Loads scriptfiles/.env. Returns 1 if the file was found, 0 otherwise.
stock LoadServerConfig()
{
    new File:handle = fopen(".env", io_read);
    if(!handle)
    {
        print("[CONFIG] scriptfiles/.env not found - using built-in defaults.");
        return 0;
    }

    new line[160];
    while(fread(handle, line)) Env_ParseLine(line);
    fclose(handle);

    printf("[CONFIG] Loaded .env: db=%s@%s/%s | name=%s | id=%d",
        ENV_MYSQL_USER, ENV_MYSQL_HOST, ENV_MYSQL_DB, ENV_SERVER_NAME, ENV_SERVER_ID);
    return 1;
}

#endif
