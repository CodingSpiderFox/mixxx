#ifndef SVGPARSER_H
#define SVGPARSER_H

#include <QHash>
#include <QString>
#include <QDomNode>
#include <QDomElement>
#include <QScriptEngine>
#include <QDir>

#include "skin/skincontext.h"


// A class for managing the svg files
class SvgParser {
  public:
    SvgParser();
    SvgParser(const SkinContext& parent);
    virtual ~SvgParser();


    // Variable lookup and modification methods.
    QString variable(const QString& name) const;
    const QHash<QString, QString>& variables() const {
        return m_variables;
    }
    void setVariable(const QString& name, const QString& value);


    // Updates the SkinContext with all the <SetVariable> children of node.
    void updateVariables(const QDomNode& node);
    // Updates the SkinContext with 'element', a <SetVariable> node.
    void updateVariable(const QDomElement& element);

    // Methods for evaluating nodes given the context.
    QDomDocument getDocument(const QDomNode& node) const;
    void scanTree(const QDomNode& node, void (SvgParser::*callback)(const QDomNode& node)const) const;


    QDomNode parseSvgTree(const QDomNode& svgSkinNode) const;
    QDomNode parseSvgFile(const QString& svgFileName) const;
    QString saveToTempFile(const QDomNode& svgNode) const;
    QByteArray saveToQByteArray(const QDomNode& svgNode) const;
    void parseVariableElements(const QDomNode& svgNode) const;


  private:
    void parseAttributes(const QDomNode& node) const;
    void parseScriptElements(const QDomNode& svgNode) const;
    QScriptValue evaluateTemplateExpression(QString expression) const;
    
    mutable QScriptEngine m_scriptEngine;
    QHash<QString, QString> m_variables;
    QString m_skinBasePath;
    const SkinContext * m_pContext;
    
};

#endif /* SVGPARSER_H */
