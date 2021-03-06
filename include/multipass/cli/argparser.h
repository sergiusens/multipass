/*
 * Copyright (C) 2017 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef ARGPARSER_H
#define ARGPARSER_H

#include <QtCore/QCommandLineOption>
#include <QtCore/QCommandLineParser>

#include "command.h"

namespace multipass
{
class ArgParser
{
    // Note: We are using camelCase here for methods since this class mimics the QCommandLineParser class

public:
    ArgParser(const QStringList& arguments, const std::vector<cmd::Command::UPtr>& commands, std::ostream& cout,
              std::ostream& cerr);

    void setApplicationDescription(const QString& description);

    bool addOption(const QCommandLineOption& command_line_option);
    bool addOptions(const QList<QCommandLineOption>& options);

    void addPositionalArgument(const QString& name, const QString& description, const QString& syntax = QString());

    ParseCode parse();
    cmd::Command* chosenCommand() const;
    cmd::Command* findCommand(const QString& command) const;

    bool isSet(const QCommandLineOption& option) const;

    QString value(const QCommandLineOption& option) const;
    QStringList values(const QCommandLineOption &option) const;

    QStringList positionalArguments() const;

    ParseCode commandParse(cmd::Command* command);

    ReturnCode returnCodeFrom(ParseCode parse_code) const;

    void forceCommandHelp();
    void forceGeneralHelp();

private:
    QString generalHelpText();
    QString helpText(cmd::Command* command);

    const QStringList& arguments;
    const std::vector<cmd::Command::UPtr>& commands;
    cmd::Command* chosen_command;

    QCommandLineParser parser;

    bool help_requested;

    std::ostream& cout;
    std::ostream& cerr;
};
} // namespace multipass
#endif // ARGPARSER_H
