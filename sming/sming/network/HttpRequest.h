/****
 * Sming Framework Project - Open Source framework for high efficiency native ESP8266 development.
 * Created 2015 by Skurydin Alexey
 * http://github.com/anakod/Sming
 * All files of the Sming Core are provided under the LGPL v3 license.
 ****/

#ifndef _SMING_CORE_NETWORK_HTTPREQUEST_H_
#define _SMING_CORE_NETWORK_HTTPREQUEST_H_

#define NETWORK_MAX_HTTP_PARSING_LEN 4096

#include "../wiring/WHashMap.h"
#include "../wiring/WString.h"

class pbuf;
class HttpServer;
class TemplateFileStream;

enum HttpParseResult
{
	eHPR_Wait = 0,
	eHPR_Successful,
	eHPR_Failed
};

class HttpRequest
{
public:
	HttpRequest();
	virtual ~HttpRequest();

	inline String getRequestMethod() { return method; }
	inline String getPath() { return path; }
	String getContentType();
	int getContentLength();

	bool isAjax();
	bool isWebSocket();
	bool isCommandRequest();

	String getQueryParameter(String parameterName, String defaultValue = "");
	String getPostParameter(String parameterName, String defaultValue = "");
	String getHeader(String headerName, String defaultValue = "");
	String getCookie(String cookieName, String defaultValue = "");
	char* getBody();

public:
	HttpParseResult parseHeader(HttpServer *server, pbuf* buf);
	HttpParseResult parsePostData(HttpServer *server, pbuf* buf);
	bool extractParsingItemsList(pbuf* buf, int startPos, int endPos,
			char delimChar, char endChar,
			HashMap<String, String> *resultItems);
	void parseRawData(HttpServer *server, pbuf* buf);

private:
	String method;
	String path;
	HashMap<String, String> *requestHeaders;
	HashMap<String, String> *requestGetParameters;
	HashMap<String, String> *requestPostParameters;
	HashMap<String, String> *cookies;
	int postDataProcessed;
	bool combinePostFrag;
	char *bodyBuf;

	friend class TemplateFileStream;
};

#endif /* _SMING_CORE_NETWORK_HTTPREQUEST_H_ */
