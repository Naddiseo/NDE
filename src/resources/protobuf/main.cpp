#include <iostream>
#include <fstream>

#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include "resource.pb.h"

using namespace std;
namespace pb = google::protobuf;

int
main(int argc, char** argv)
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	if (argc != 2) {
		cerr << "Usage:  " << argv[0] << " <resource file>" << endl;
		return -1;
	}

	nde::Mesh mesh;

	{
		fstream input(argv[1], ios::in | ios::binary);
		pb::io::IstreamInputStream input2(&input);
		
		if (!pb::TextFormat::Parse(&input2, &mesh)) {
			cerr << "Failed to parse mesh." << endl;
			return -1;
		}
	}
	
  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
