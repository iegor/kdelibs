/* Automatically generated from ./xmlhttprequest.cpp using ../../kjs/create_hash_table. DO NOT EDIT ! */

using namespace KJS;

namespace KJS {

static const char XMLHttpRequestProtoTableStrings[] = {
    "\0"
    "getAllResponseHeaders\0"
    "getResponseHeader\0"
    "overrideMimeType\0"
    "setRequestHeader\0"
    "abort\0"
    "open\0"
    "send\0"
};


static const struct HashEntry XMLHttpRequestProtoTableEntries[] = {
   { 81, XMLHttpRequest::Open, DontDelete|Function, 5, -1 },
   { 41, XMLHttpRequest::OverrideMIMEType, DontDelete|Function, 1, -1 },
   { 23, XMLHttpRequest::GetResponseHeader, DontDelete|Function, 1, -1 },
   { 58, XMLHttpRequest::SetRequestHeader, DontDelete|Function, 2, -1 },
   { 75, XMLHttpRequest::Abort, DontDelete|Function, 0, -1 },
   { 0, 0, 0, 0, -1 },
   { 1, XMLHttpRequest::GetAllResponseHeaders, DontDelete|Function, 0, 7 },
   { 86, XMLHttpRequest::Send, DontDelete|Function, 1, -1 }
};

const struct HashTable XMLHttpRequestProtoTable = { 2, 8, XMLHttpRequestProtoTableEntries, 7, XMLHttpRequestProtoTableStrings};

} // namespace

using namespace KJS;

namespace KJS {

static const char XMLHttpRequestTableStrings[] = {
    "\0"
    "onreadystatechange\0"
    "responseText\0"
    "responseXML\0"
    "readyState\0"
    "statusText\0"
    "onload\0"
    "status\0"
};


static const struct HashEntry XMLHttpRequestTableEntries[] = {
   { 33, XMLHttpRequest::ResponseXML, DontDelete|ReadOnly, 0, 8 },
   { 0, 0, 0, 0, -1 },
   { 1, XMLHttpRequest::Onreadystatechange, DontDelete, 0, -1 },
   { 45, XMLHttpRequest::ReadyState, DontDelete|ReadOnly, 0, -1 },
   { 74, XMLHttpRequest::Status, DontDelete|ReadOnly, 0, -1 },
   { 20, XMLHttpRequest::ResponseText, DontDelete|ReadOnly, 0, 7 },
   { 0, 0, 0, 0, -1 },
   { 56, XMLHttpRequest::StatusText, DontDelete|ReadOnly, 0, -1 },
   { 67, XMLHttpRequest::Onload, DontDelete, 0, -1 }
};

const struct HashTable XMLHttpRequestTable = { 2, 9, XMLHttpRequestTableEntries, 7, XMLHttpRequestTableStrings};

} // namespace
