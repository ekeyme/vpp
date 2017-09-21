/*
 * Copyright (c) 2017 Cisco Systems, Inc. and others.  All rights reserved.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License v1.0 which accompanies this distribution,
 * and is available at http://www.eclipse.org/legal/epl-v10.html
 */

#ifndef __VOM_INSPECT_H__
#define __VOM_INSPECT_H__

#include <map>
#include <deque>
#include <string>
#include <ostream>

namespace VOM
{
    /**
     * A means to inspect the state VPP has built, in total, and per-client
     */
    class inspect
    {
    public:
        /**
         * Constructor
         */
        inspect() = default;

        /**
         * Destructor to tidyup socket resources
         */
        ~inspect() = default;

        /**
         * handle input from the requester
         *
         * @param input command
         * @param output output
         */
        void handle_input(const std::string &input,
                          std::ostream &output);

        /**
         * inspect command handler Handler
         */
        class command_handler
        {
        public:
            command_handler() = default;
            virtual ~command_handler() = default;

            /**
             * Show each object
             */
            virtual void show(std::ostream &os) = 0;
        };

        /**
         * Register a command handler for inspection
         */
        static void register_handler(const std::vector<std::string> &cmds,
                                     const std::string &help,
                                     command_handler *ch);
    private:
        /**
         * command handler list
         */
        static std::unique_ptr<std::map<std::string, command_handler*>> m_cmd_handlers;
        /**
         * help handler list
         */
        static std::unique_ptr<std::deque<std::pair<std::vector<std::string>, std::string>>> m_help_handlers;
    };
};

#endif