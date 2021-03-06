#ifndef OCRCorrection_SimpleOutputWriter_h__
#define OCRCorrection_SimpleOutputWriter_h__

namespace OCRCorrection {
        class Document;
        class Token;

        class SimpleOutputWriter {
        public:
                SimpleOutputWriter(const Document& document);
                void write() const;

        private:
                void writeNormalToken(const Token& token) const;
                const Document& document_;
        };
}

#endif // OCRCorrection_SimpleOutputWriter_h__
