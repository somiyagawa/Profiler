#include "AutoCorrector.h"
#include "Document/Document.h"
#include "Utils/Utils.h"

using namespace OCRCorrection;

////////////////////////////////////////////////////////////////////////////////
void
AutoCorrector::add_patterns(const std::string& pats)
{
	size_t i = -1;
	do {
		++i;
		const auto pos = pats.find(",", i);
		add_pattern(pats.substr(i, pos -i));
		i = pos;
	} while (i != std::string::npos);
}

////////////////////////////////////////////////////////////////////////////////
void
AutoCorrector::add_pattern(const std::string& pat)
{
	patterns_.push_back(Utils::tolower(Utils::utf8(pat)));
}

////////////////////////////////////////////////////////////////////////////////
void
AutoCorrector::correct(Document& doc) const
{
	for (auto& token: doc) {
		if (not token.isNormal()) // skip not normal token
			continue;
		if (not token.has_metadata("groundtruth"))
			throw std::runtime_error("Cannot autocorrect "
					"without groundtruth");
		for (const auto& pat: patterns_) {
			if (token.getWOCR_lc().find(pat) != std::string::npos) {
				token.metadata()["correction"] =
					token.metadata()["groundtruth"];
				token.metadata()["correction-lc"] =
					token.metadata()["groundtruth-lc"];
				std::wcout << "Correcting token " << token.getWOCR()
					   << " with "
					   << token.metadata()["correction"] << "\n";
				break; // correct each token once
			}
		}
	}
}