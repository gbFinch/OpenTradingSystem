//
// Created by Solar on 10/20/2020.
//

#ifndef CPP_DERIBIT_GIT_H
#define CPP_DERIBIT_GIT_H

#include <string>

class VersionMetadata {
public:
    // Is the metadata populated? We may not have metadata if
    // there wasn't a .git directory (e.g. downloaded source
    // code without revision history).
    static bool Populated();

    // Were there any uncommitted changes that won't be reflected
    // in the CommitID?
    static bool AnyUncommittedChanges();

    // The commit author's name.
    static const char * AuthorName();
    // The commit author's email.
    static const char * AuthorEmail();
    // The commit SHA1.
    static const char * CommitSHA1();
    // The ISO8601 commit date.
    static const char * CommitDate();
    // The commit subject.
    static const char * CommitSubject();
    // The commit body.
    static const char * CommitBody();
    // The commit describe.
    static const char * Describe();
    // The commit branch name
    static const char * BranchName();
};

#define REGISTER_VERSION() std::string GetVersion() override { return std::string(VersionMetadata::BranchName()) + "/" + VersionMetadata::Describe(); }

#endif //CPP_DERIBIT_GIT_H
