// -*- C++ -*-
//
// This file is part of LHAPDF
// Copyright (C) 2012-2013 The LHAPDF collaboration (see AUTHORS for details)
//
#include "LHAPDF/PDFInfo.h"
#include "LHAPDF/PDFSet.h"
#include "LHAPDF/Factories.h"

namespace LHAPDF {


  /// Constructor from a set name and member ID.
  PDFInfo::PDFInfo(const std::string& setname, int member) {
    _setname = setname;
    _member = member;
    const string searchpath = findFile(pdfmempath(setname, member));
    if (searchpath.empty())
      throw ReadError("Couldn't find a PDF data file for " + setname + " #" + to_str(member));
    load(searchpath);
  }


  /// Constructor from an LHAPDF ID code.
  PDFInfo::PDFInfo(int lhaid) {
    const pair<string,int> setname_memid = lookupPDF(lhaid);
    if (setname_memid.second == -1)
      throw IndexError("Can't find a PDF with LHAPDF ID = " + to_str(lhaid));
    _setname = setname_memid.first; _member = setname_memid.second;
    const string searchpath = pdfmempath(setname_memid.first, setname_memid.second);
    if (searchpath.empty())
      throw ReadError("Couldn't find a PDF data file for LHAPDF ID = " + to_str(lhaid));
    load(searchpath);
  }


  bool PDFInfo::has_key(const string& key) const {
    // cout << key << " in PDF: " << boolalpha << has_key_local(key) << endl;
    // cout << key << " in Set: " << boolalpha << getPDFSet(_setname).has_key(key) << endl;
    // cout << key << " in Cfg: " << boolalpha << getConfig().has_key(key) << endl;
    return has_key_local(key) || getPDFSet(_setname).has_key(key);
  }


  const std::string& PDFInfo::get_entry(const string& key) const {
    if (has_key_local(key)) return get_entry_local(key); //< value is defined locally
    return getPDFSet(_setname).get_entry(key); //< fall back to the set-level info... or beyond
  }


}
