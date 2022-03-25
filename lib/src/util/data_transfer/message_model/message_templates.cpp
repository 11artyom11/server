#include "../../../../include/util/data_transfer/message_model/message_templates.h"


using namespace DataTransfer;

ConnectRequest::ConnectRequest(const string& ip)
{
    Debug().info ("Constructed ConnectRequest Message");
    this->set ("command", this->command);
    this->set ("ip", ip);
}

ConnectAccept::ConnectAccept(const string& pkey)
{
    Debug().info ("Constructed ConnectAccept Message");
    this->set ("command", this->command);
    this->set ("pkey", pkey);
}

ConnectCommand::ConnectCommand(const string& ip ,
                                    const string& AES_token)
{
    Debug().info ("Constructed ConnectCommand Message");
    this->set("command", command);
    this->set("ip", ip);
    this->set("aes_token", AES_token);
}

ConnectVerify::ConnectVerify(const string& tmp_uid)
{
    Debug().info ("Constructed ConnectVerify Message");
    this->set ("command", command);
    this->set ("tmp_uid", tmp_uid);
}

LoginRequest::LoginRequest(const string& ip)
{
    Debug().info ("Constructed LoginRequest Message");
    this->set ("command", command);
    this->set ("ip", ip);
}

LoginAccept::LoginAccept(void)
{
    Debug().info ("Constructed LoginAccept Message");
    this->set ("command", command);
}

LoginCommand::LoginCommand(const string& name,
                                const string& password)
{
    Debug().info ("Constructed LoginCommand Message");
    this->set ("command", command);
    this->set ("name", name);
    this->set ("passwd", password);
}

LoginVerify::LoginVerify(const string&  perm_uid)
{
    Debug().info ("Constructed LoginVerify Message");
    this->set ("command", command);
    this->set ("perm_uid", perm_uid);
}

SignUpCommand::SignUpCommand(const string& ip,
                                const string& name,
                                    const string& dial,
                                    const string& email,
                                        const string& passwd)
{
    Debug().info ("Constructed SignUpCommand Message");
    this->set ("command", command);
    this->set ("ip", ip);
    this->set ("name", name);
    this->set ("dial", dial);
    this->set ("email", email);
    this->set ("passwd", passwd);
}

SignUpVerify::SignUpVerify(const string& perm_uid)
{
    Debug().info ("Constructed SignUpVerify Message");
    this->set ("command", command);
    this->set ("perm_uid", perm_uid);
}