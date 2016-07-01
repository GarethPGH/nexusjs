/*
 * Nexus.js - The next-gen JavaScript platform
 * Copyright (C) 2016  Abdullah A. Hassan <abdullah@webtomizer.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "classes/net/http/connection.h"
#include "classes/net/http/request.h"
#include "classes/net/http/response.h"

const JSClassDefinition NX::Classes::Net::HTTP::Connection::Class {
  0, kJSClassAttributeNone, "HTTPConnection", nullptr, NX::Classes::Net::HTTP::Connection::Properties,
  NX::Classes::Net::HTTP::Connection::Methods, nullptr
};

const JSStaticValue NX::Classes::Net::HTTP::Connection::Properties[] {
//   { "request", [](JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception) -> JSValueRef {
//     try {
//       NX::Context * context = Context::FromJsContext(ctx);
//       NX::Classes::Net::HTTP::Connection * conn = NX::Classes::Net::HTTP::Connection::FromObject(object);
//       if (!conn)
//         throw std::runtime_error(".request not implemented on Connection object");
//       return conn->requestObject();
//     } catch(const std::exception & e) {
//       return JSWrapException(ctx, e, exception);
//     }
//   },
//   nullptr, kJSPropertyAttributeNone },
  { nullptr, nullptr, nullptr, 0 }
};

const JSStaticFunction NX::Classes::Net::HTTP::Connection::Methods[] {
  { nullptr, nullptr, 0 }
};

JSObjectRef NX::Classes::Net::HTTP::Connection::start(NX::Context * context, JSObjectRef thisObject)
{
  NX::Object thisObj(context->toJSContext(), thisObject);
  NX::Classes::Net::HTTP::Request * req = new NX::Classes::Net::HTTP::Request(this);
  NX::Classes::Net::HTTP::Response * res = new NX::Classes::Net::HTTP::Response(this);
  JSObjectRef reqObj = JSObjectMake(context->toJSContext(), NX::Classes::Net::HTTP::Request::createClass(context), req);
  JSObjectRef resObj = JSObjectMake(context->toJSContext(), NX::Classes::Net::HTTP::Response::createClass(context), res);
  thisObj.set("request", reqObj);
  thisObj.set("response", resObj);
  return NX::Object(context->toJSContext(), NX::Globals::Promise::all(context->toJSContext(), std::vector<JSValueRef> {
    req->attach(context->toJSContext(), reqObj),
    res->attach(context->toJSContext(), resObj)
  })).then([=](JSContextRef ctx, JSValueRef value, JSValueRef * exception){
    return thisObject;
  });
}