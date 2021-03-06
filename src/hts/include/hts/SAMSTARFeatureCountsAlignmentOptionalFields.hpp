//
//  SAMSTARFeatureCountsAlignmentOptionalFields.hpp
//  High-Throughput-Sequencing
//
//  Created by Yuguang Xiong on 3/29/18.
//  Copyright © 2018 Granville Xiong. All rights reserved.
//

#ifndef SAMSTARFeatureCountsAlignmentOptionalFields_hpp
#define SAMSTARFeatureCountsAlignmentOptionalFields_hpp

#include "vector"
#include <utk/StringUtils.hpp>
#include "SAMAlignmentOptionalFields.hpp"

namespace hts
{

/// \brief A class to access optional fields specific to STAR and featureCounts.
/// This class needs to access three custom optional fields in alignment line of
/// the SAM file, generated by the report mode of featureCounts program:
///
/// 1) The alignment status (XS).
/// 2) The number of target features (XN), e.g. genes, which a sequence is
///    aligned to.
/// 3) A list of target features (XT).
class SAMSTARFeatureCountsAlignmentOptionalFields : public SAMAlignmentOptionalFields
{
public:

    static constexpr char comma_sep {','};
    
public:

    /// Default initializer.
    SAMSTARFeatureCountsAlignmentOptionalFields();

    /// \brief Initialization with multiple copies of specified element.
    SAMSTARFeatureCountsAlignmentOptionalFields(std::size_t count, const SAMAlignmentOptionalField& opt_field);

    /// \brief Initialization with multiple copies of default element.
    SAMSTARFeatureCountsAlignmentOptionalFields(std::size_t count);

    /// \brief Initialization with a range of iterators.
    template<class InputIterator>
    SAMSTARFeatureCountsAlignmentOptionalFields(InputIterator first, InputIterator last);

    SAMSTARFeatureCountsAlignmentOptionalFields(const SAMSTARFeatureCountsAlignmentOptionalFields& opt_fields);

    SAMSTARFeatureCountsAlignmentOptionalFields(SAMSTARFeatureCountsAlignmentOptionalFields&& opt_fields);

    virtual ~SAMSTARFeatureCountsAlignmentOptionalFields() noexcept;

    SAMSTARFeatureCountsAlignmentOptionalFields& operator=(const SAMSTARFeatureCountsAlignmentOptionalFields& opt_fields);

    SAMSTARFeatureCountsAlignmentOptionalFields& operator=(SAMSTARFeatureCountsAlignmentOptionalFields&& opt_fields);

    SAMSTARFeatureCountsAlignmentOptionalFields& operator=(std::initializer_list<SAMAlignmentOptionalField> opt_fields);

    /// Check if the tag of alignement status exists.
    bool hasAlignmentStatus() const
    {
        return hasTag("XS");
    }

    /// Get alignement status (an inefficient version).
    const std::string& getAlignmentStatus() const
    {
        return getValue("XS");
    }

    /// Get alignement status (an efficient version).
    bool getAlignmentStatus(std::string& value) const
    {
        return getValue("XS", value);
    }

    /// Check if the tag of the number of target features exists.
    bool hasNumberOfTargetFeatures() const
    {
        return hasTag("XN");
    }

    /// Get the number of target features (an inefficient version).
    std::size_t getNumberOfTargetFeatures() const
    {
        return utk::convert<std::size_t>(getValue("XN"));
    }

    /// Get the number of target features (an efficient version).
    bool getNumberOfTargetFeatures(std::size_t& value) const
    {
        std::string buf;
        bool status = getValue("XN", buf);
        if(status) value = utk::convert<std::size_t>(buf);
        return status;
    }

    /// Check if the tag of target features exists.
    bool hasTargetFeatures() const
    {
        return hasTag("XT");
    }

    /// Get a list of target features (an inefficient version).
    std::vector<std::string> getTargetFeatures() const
    {
        return utk::splitString(getValue("XT"), comma_sep);
    }

    /// Get a list of target features (an efficient version).
    bool getTargetFeatures(std::vector<std::string>& value) const
    {
        std::string buf;
        bool status = getValue("XT", buf);
        if(status) value = utk::splitString(buf, comma_sep);
        return status;
    }
};

}

#endif /* SAMSTARFeatureCountsAlignmentOptionalFields_hpp */
