#ifndef OCRCorrection_AutoCorrector_h__
#define OCRCorrection_AutoCorrector_h__

#include <vector>
#include <string>

namespace OCRCorrection {
	class Document;
	class Token;

	class AutoCorrector {
	public:
		void add_patterns(const std::string& pat);
		void add_pattern(const std::string& pat);
		void operator()(Document& doc) const {correct(doc);}
		void correct(Document& doc) const;

	private:
		struct CorrectPercent {};
		struct CorrectPatterns {};
		void correct(Document& doc, CorrectPercent) const;
		void correct(Document& doc, CorrectPatterns) const;
		void correct(Token& token) const;
		struct Pattern {
			using It = std::wstring::const_iterator;
			Pattern(std::wstring g, std::wstring o, int p)
				: gt(std::move(g))
				, ocr(std::move(o))
				, n(p)
			{}
			bool match(const Token& token) const;
			static bool match(It fb, It fe, It b, It e);

			std::wstring gt, ocr;
			double n;
		};
		std::vector<Pattern> patterns_;
		double percent_;
	};
}

#endif // OCRCorrection_AutoCorrector_h__
