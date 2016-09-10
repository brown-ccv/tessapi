// tessapi.cpp : Defines the entry point for the console application.
//

#include "TessAPI_Wrapper.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

namespace py = pybind11;

PYBIND11_PLUGIN(tessapi) {
	py::module m("tessapi", "Tesseract API bindings for Python");

	/*py::enum_<tesseract::PageSegMode>(m, "PageSegMode")
		.value("PSM_OSD_ONLY", tesseract::PSM_OSD_ONLY)
		.value("PSM_AUTO_OSD", tesseract::PSM_AUTO_OSD)
		.value("PSM_AUTO_ONLY", tesseract::PSM_AUTO_ONLY)
		.value("PSM_SINGLE_COLUMN", tesseract::PSM_SINGLE_COLUMN)
		.value("PSM_SINGLE_BLOCK_VERT_TEXT", tesseract::PSM_SINGLE_BLOCK_VERT_TEXT)
		.value("PSM_SINGLE_BLOCK", tesseract::PSM_SINGLE_BLOCK)
		.value("PSM_SINGLE_LINE", tesseract::PSM_SINGLE_LINE)
		.value("PSM_SINGLE_WORD", tesseract::PSM_SINGLE_WORD)
		.value("PSM_CIRCLE_WORD", tesseract::PSM_CIRCLE_WORD)
		.value("PSM_SINGLE_CHAR", tesseract::PSM_SINGLE_CHAR)
		.value("PSM_SPARSE_TEXT", tesseract::PSM_SPARSE_TEXT)
		.value("PSM_SPARSE_TEXT_OSD", tesseract::PSM_SPARSE_TEXT_OSD)
		.value("PSM_RAW_LINE", tesseract::PSM_RAW_LINE)
		.export_values();*/

	py::enum_<FontAttribute>(m, "FontAttribute")
		.value("PLAIN", FontAttribute::PLAIN)
		.value("BOLD", FontAttribute::BOLD)
		.value("ITALIC", FontAttribute::ITALIC)
		.value("UNDER_LINED", FontAttribute::UNDER_LINED)
		.export_values();
	
	py::class_<FontAttrLabel>(m, "FontAttrLabel")
		.def(py::init<>())
		.def(py::init<FontAttribute, uint16_t, uint16_t, uint16_t>())
		.def_readwrite("attr", &FontAttrLabel::attr, "font attribute category (PLAIN, BOLD, ITALIC, or UNDER_LINED)")
		.def_readwrite("point_size", &FontAttrLabel::point_size, "font size")
		.def_readwrite("start", &FontAttrLabel::start, "start position, inclusive")
		.def_readwrite("length", &FontAttrLabel::length);

	//TODO: bind some functions for getting tesseract config values
	py::class_<TessAPI_Wrapper>(m, "TessBaseAPI")
		.def(py::init<>())
		.def("SetVariable", &TessAPI_Wrapper::SetVariable_wrap, "Set a config variable for tesseract, returns false if name lookup failed.\n"
																"Notable variables include 'tessedit_pageseg_mode' and 'tessedit_char_whitelist'.")
		.def("SetImage", &TessAPI_Wrapper::SetImage_cv2, "Set the image tesseract will work with. (uses opencv2-numpy image)")
		.def("ReadConfigFile", &TessAPI_Wrapper::ReadConfigFile_wrap, "Read-in a config file.")
		.def("MeanTextConf", &TessAPI_Wrapper::MeanTextConf_wrap, "Mean confidence of all words recognized on this image.")
		.def("TotalConfidence", &TessAPI_Wrapper::TotalConfidence, "Returns a tuple of sum of confidence scores and number of words i.e. (total_confidence, num_words)."
			" Use this for getting a mean confidence over multiple images.")
		.def("SetRectangle", &TessAPI_Wrapper::SetRectangle_wrap, "Set the bounding rectangle tesseract will use when reading text."
			" ((x,y) is the top left corner of that box)",
			py::arg("x"), py::arg("y"), py::arg("w"), py::arg("h"))
		.def("RegisterSpellCheckCallback", &TessAPI_Wrapper::RegisterSpellCheckCallback, "Registers a function to be called on each ocred word in the order they appear.\n"
																						 "The function is called with (str word, float confidence) arguments and is expected\n"
																						 "to return the spellchecked version of the given word.")
		.def("RemoveSpellCheckCallback", &TessAPI_Wrapper::RemoveSpellCheckCallback)
		.def("GetText", &TessAPI_Wrapper::GetText, "Gets plain OCRed text.")
		.def("GetTextWithAttrs", &TessAPI_Wrapper::GetTextWithAttrs, "Gets OCRed text with font attribute information (i.e. categorized as PLAIN, BOLD,\n"
																	 "ITALIC, or UNDER_LINED & font point size) Return value is a tuple with the OCRed text and\n"
																	 "a list of FontAttrLabels with start, length, attr and point_size members");
	   //.def("SetPageSegMode", &TessAPI_Wrapper::SetPageSegMode, "Set the page segment mode.")
	   //.def("GetPageSegMode", &TessAPI_Wrapper::GetPageSegMode, "Get the page segment mode.");

	return m.ptr();
}
