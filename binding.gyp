{
  "targets": [
    {
      "target_name": "nbiobsp",
      "sources": [ "nbiobsp.cpp" ],
      "libraries": [
        "-lNBioBSP", "-L/lib"
      ],
      "cflags": ["-Wall", "-std=c++11", "-lNBioBSP"],
    }
  ]
}