#pragma once

#	define NDE_NS nde
#	define NDE_NS_BEGIN namespace nde {
#	define NDE_NS_END   }

#if 1
#	define NDESCRIPT_NS NDE_NS script
#	define NDESCRIPT_NS_BEGIN NDE_NS_BEGIN namespace script {
#	define NDESCRIPT_NS_END   } NDE_NS_END
#else
#	define NDESCRIPT_NS
#	define NDESCRIPT_NS_BEGIN
#	define NDESCRIPT_NS_END
#endif
