// EnergyPlus, Copyright (c) 1996-2020, The Board of Trustees of the University of Illinois,
// The Regents of the University of California, through Lawrence Berkeley National Laboratory
// (subject to receipt of any required approvals from the U.S. Dept. of Energy), Oak Ridge
// National Laboratory, managed by UT-Battelle, Alliance for Sustainable Energy, LLC, and other
// contributors. All rights reserved.
//
// NOTICE: This Software was developed under funding from the U.S. Department of Energy and the
// U.S. Government consequently retains certain rights. As such, the U.S. Government has been
// granted for itself and others acting on its behalf a paid-up, nonexclusive, irrevocable,
// worldwide license in the Software to reproduce, distribute copies to the public, prepare
// derivative works, and perform publicly and display publicly, and to permit others to do so.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted
// provided that the following conditions are met:
//
// (1) Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//
// (2) Redistributions in binary form must reproduce the above copyright notice, this list of
//     conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//
// (3) Neither the name of the University of California, Lawrence Berkeley National Laboratory,
//     the University of Illinois, U.S. Dept. of Energy nor the names of its contributors may be
//     used to endorse or promote products derived from this software without specific prior
//     written permission.
//
// (4) Use of EnergyPlus(TM) Name. If Licensee (i) distributes the software in stand-alone form
//     without changes from the version obtained under this License, or (ii) Licensee makes a
//     reference solely to the software portion of its product, Licensee must refer to the
//     software as "EnergyPlus version X" software, where "X" is the version number Licensee
//     obtained under this License and may not use a different name for the software. Except as
//     specifically required in this Section (4), Licensee shall not use in a company name, a
//     product name, in advertising, publicity, or other promotional activities any name, trade
//     name, trademark, logo, or other designation of "EnergyPlus", "E+", "e+" or confusingly
//     similar designation, without the U.S. Department of Energy's prior written consent.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

// Google Test Headers
#include <gtest/gtest.h>

// EnergyPlus Headers
#include "Fixtures/EnergyPlusFixture.hh"
#include <EnergyPlus/ConfiguredFunctions.hh>
#include <EnergyPlus/CurveManager.hh>
#include <EnergyPlus/DataAirLoop.hh>
#include <EnergyPlus/DataAirSystems.hh>
#include <EnergyPlus/DataContaminantBalance.hh>
#include <EnergyPlus/DataEnvironment.hh>
#include <EnergyPlus/DataGlobalConstants.hh>
#include <EnergyPlus/DataGlobals.hh>
#include <EnergyPlus/DataHVACGlobals.hh>
#include <EnergyPlus/DataHeatBalance.hh>
#include <EnergyPlus/DataHeatBalFanSys.hh>
#include <EnergyPlus/DataLoopNode.hh>
#include <EnergyPlus/DataSizing.hh>
#include <EnergyPlus/DataZoneControls.hh>
#include <EnergyPlus/DataZoneEnergyDemands.hh>
#include <EnergyPlus/DataZoneEquipment.hh>
#include <EnergyPlus/EvaporativeCoolers.hh>
#include <EnergyPlus/FileSystem.hh>
#include <EnergyPlus/General.hh>
#include <EnergyPlus/HeatBalanceManager.hh>
#include <EnergyPlus/Humidifiers.hh>
#include <EnergyPlus/HybridEvapCoolingModel.hh>
#include <EnergyPlus/HybridUnitaryAirConditioners.hh>
#include <EnergyPlus/MixedAir.hh>
#include <EnergyPlus/OutputFiles.hh>
#include <EnergyPlus/OutputReportPredefined.hh>
#include <EnergyPlus/Psychrometrics.hh>
#include <EnergyPlus/ReportSizingManager.hh>
#include <EnergyPlus/ScheduleManager.hh>
#include <EnergyPlus/SizingManager.hh>
#include <EnergyPlus/SystemReports.hh>
#include <fstream>

using namespace EnergyPlus::MixedAir;
using namespace EnergyPlus::DataContaminantBalance;
using namespace EnergyPlus::DataAirLoop;
using namespace EnergyPlus::DataAirSystems;
using namespace EnergyPlus::DataSizing;
using namespace EnergyPlus::DataHeatBalance;
using namespace EnergyPlus::ScheduleManager;
using namespace EnergyPlus::DataEnvironment;
using namespace EnergyPlus::DataHeatBalFanSys;
using namespace EnergyPlus::DataZoneEquipment;
using namespace EnergyPlus::DataLoopNode;
using namespace EnergyPlus::DataZoneEnergyDemands;
using namespace EnergyPlus::DataZoneControls;
using namespace EnergyPlus::HeatBalanceManager;
using namespace EnergyPlus::Humidifiers;
using namespace EnergyPlus::OutputReportPredefined;
using namespace EnergyPlus::ReportSizingManager;
using namespace EnergyPlus::SizingManager;
using namespace EnergyPlus::SystemReports;

using namespace EnergyPlus::DataContaminantBalance;
using namespace EnergyPlus::MixedAir;
using namespace EnergyPlus;
using namespace EnergyPlus::SizingManager;
using EnergyPlus::CurveManager::CurveValue;
using EnergyPlus::CurveManager::GetCurveName;
using EnergyPlus::CurveManager::GetNormalPoint;
using EnergyPlus::Psychrometrics::PsyHFnTdbRhPb;
using EnergyPlus::Psychrometrics::PsyRhFnTdbWPb;
using EnergyPlus::Psychrometrics::PsyWFnTdbRhPb;
using namespace EnergyPlus::ScheduleManager;
using EnergyPlus::HybridEvapCoolingModel::CMode;
using EnergyPlus::HybridEvapCoolingModel::CSetting;
using EnergyPlus::HybridEvapCoolingModel::Model;
using namespace EnergyPlus::HybridUnitaryAirConditioners;

namespace EnergyPlus {
std::vector<std::string> getAllLinesInFile2(std::string filePath)
{
    std::ifstream infile(filePath);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }
    return lines;
}

std::vector<std::string> parseLine(std::string line)
{
    std::vector<std::string> vect;
    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, ',')) {
        vect.push_back(token);
    }
    return vect;
}

TEST_F(EnergyPlusFixture, UnitaryHybridAirConditioner_HighCooling)
{
    std::vector<std::string> snippet = getAllLinesInFile2(configured_source_directory() + "/tst/EnergyPlus/unit/UnitaryHybridUnitTest_DOSA.idf");
    std::string string = delimited_string(snippet);
    ASSERT_TRUE(process_idf(string));
    // setup environment
    bool ErrorsFound(false);
    GetZoneData(ErrorsFound);
    EXPECT_FALSE(ErrorsFound);
    // Initialize schedule values
    DataGlobals::TimeStep = 1;
    DataHVACGlobals::TimeStepSys = 1;
    DataGlobals::NumOfTimeStepInHour = 1;
    DataGlobals::MinutesPerTimeStep = 60;
    DataEnvironment::Month = 1;
    DataEnvironment::DayOfMonth = 21;
    DataGlobals::HourOfDay = 1;
    DataEnvironment::DSTIndicator = 0;
    DataEnvironment::DayOfWeek = 2;
    DataEnvironment::HolidayIndex = 0;
    DataGlobals::WarmupFlag = false;
    DataEnvironment::DayOfYear_Schedule = General::OrdinalDay(Month, DayOfMonth, 1);
    ScheduleManager::UpdateScheduleValues();
    // Initialize zone areas and volumes - too many other things need to be set up to do these in the normal routines
    DataHeatBalance::Zone(1).FloorArea = 232.26;
    DataEnvironment::StdRhoAir = 1.225;
    DataHeatBalance::ZoneIntGain.allocate(1);

    SizingManager::GetOARequirements();
    GetOAControllerInputs(OutputFiles::getSingleton());
    using DataZoneEquipment::CalcDesignSpecificationOutdoorAir;

    // Setup performnace tables
    using namespace EnergyPlus::DataEnvironment;
    // process schedules
    ProcessScheduleInput(OutputFiles::getSingleton()); // read schedules
    UpdateScheduleValues();
    // Get Unitary system
    GetInputZoneHybridUnitaryAirConditioners(ErrorsFound);
    // All to get OA requiremetns
    GetOARequirements();

    EXPECT_FALSE(ErrorsFound);
    // Initialize unit
    InitZoneHybridUnitaryAirConditioners(1, 1);
    Model *pZoneHybridUnitaryAirConditioner = &HybridUnitaryAirConditioners::ZoneHybridUnitaryAirConditioner(1);
    // setup local variables for model inputs
    Real64 Tosa, Tra, Wra, Wosa, RHosa, RHra, DesignMinVR, Requestedheating, RequestedCooling, Requested_Humidification, Requested_Dehumidification;
    RHosa = 0;
    std::string TimeDate;
    int modenumber = 0;
    Real64 MsaRatio, OSAF;
    MsaRatio = OSAF = 1;

    Requestedheating = RequestedCooling = Requested_Humidification = Requested_Dehumidification = 0;

    // Scenario 1: Hi Cooling

    DesignMinVR = 1.622720855;       // Zone Hybrid Unitary HVAC Requested Outdoor Air Ventilation Mass Flow Rate
    Tra = 22.93929413;               // Zone Hybrid Unitary HVAC Return Air Temperature
    Tosa = 26.67733333;              // Zone Hybrid Unitary HVAC Outside Air Temperature
    RHra = 17.3042157;               // Zone Hybrid Unitary HVAC Return Air Relative Humidity
    RHosa = 13.1602401;              // Zone Hybrid Unitary HVAC Outside Air Relative Humidity
    Requestedheating = -122396.255;  // Watts (Zone Predicted Sensible Load to Heating Setpoint Heat Transfer Rate
    RequestedCooling = -58469.99445; // Watts (Zone Predicted Sensible Load to Cooling Setpoint Heat Transfer Rate
    // Equivalent to a Zone Predicted Sensible Load to Setpoint Heat Transfer Rate [W] of -58470 w.
    // A positive value indicates a heating load, a negative value indicates a cooling load.
    Requested_Humidification = Requested_Dehumidification = 0;
    Wra = PsyWFnTdbRhPb(Tra, RHra / 100, 101.325);
    Wosa = PsyWFnTdbRhPb(Tosa, RHosa / 100, 101.325);
    pZoneHybridUnitaryAirConditioner->InletTemp = Tra;
    pZoneHybridUnitaryAirConditioner->InletHumRat = Wra;
    pZoneHybridUnitaryAirConditioner->InletEnthalpy = PsyHFnTdbRhPb(Tra, RHra / 100, 101325, "test");
    pZoneHybridUnitaryAirConditioner->InletPressure = 101325;
    pZoneHybridUnitaryAirConditioner->InletRH = RHra / 100;
    pZoneHybridUnitaryAirConditioner->SecInletTemp = Tosa;
    pZoneHybridUnitaryAirConditioner->SecInletHumRat = Wosa;
    pZoneHybridUnitaryAirConditioner->SecInletEnthalpy = PsyHFnTdbRhPb(Tosa, RHosa / 100, 101325, "test");
    pZoneHybridUnitaryAirConditioner->SecInletPressure = 101325;
    pZoneHybridUnitaryAirConditioner->SecInletRH = RHosa / 100;
    pZoneHybridUnitaryAirConditioner->Initialize(1);
    pZoneHybridUnitaryAirConditioner->InitializeModelParams();

    pZoneHybridUnitaryAirConditioner->doStep(RequestedCooling, Requestedheating, Requested_Humidification, Requested_Dehumidification, DesignMinVR);
    // output results
    modenumber = pZoneHybridUnitaryAirConditioner->PrimaryMode;
    Real64 Tsa = pZoneHybridUnitaryAirConditioner->OutletTemp;
    Real64 Msa = pZoneHybridUnitaryAirConditioner->OutletMassFlowRate;
    Real64 deliveredSC = pZoneHybridUnitaryAirConditioner->UnitSensibleCoolingRate;
    Real64 deliveredSH = pZoneHybridUnitaryAirConditioner->UnitSensibleHeatingRate;
    Real64 returnOSAF = pZoneHybridUnitaryAirConditioner->averageOSAF;
    pZoneHybridUnitaryAirConditioner->Initialize(1);
    // checks
    EXPECT_NEAR(1.0, returnOSAF, 0.001);
    EXPECT_GT(deliveredSC, 0);
    EXPECT_NEAR(0.0, deliveredSH, 0.001);
    EXPECT_LT(Tsa, Tra);
    EXPECT_GT(Msa, DesignMinVR);
}

TEST_F(EnergyPlusFixture, UnitaryHybridAirConditioner_HighCoolingLargeSys)
{
    std::vector<std::string> snippet = getAllLinesInFile2(configured_source_directory() + "/tst/EnergyPlus/unit/UnitaryHybridUnitTest_DOSA.idf");
    std::string string = delimited_string(snippet);
    ASSERT_TRUE(process_idf(string));
    // setup environment
    bool ErrorsFound(false);
    GetZoneData(ErrorsFound);
    EXPECT_FALSE(ErrorsFound);
    // Initialize schedule values
    DataGlobals::TimeStep = 1;
    DataHVACGlobals::TimeStepSys = 1;
    DataGlobals::NumOfTimeStepInHour = 1;
    DataGlobals::MinutesPerTimeStep = 60;
    DataEnvironment::Month = 1;
    DataEnvironment::DayOfMonth = 21;
    DataGlobals::HourOfDay = 1;
    DataEnvironment::DSTIndicator = 0;
    DataEnvironment::DayOfWeek = 2;
    DataEnvironment::HolidayIndex = 0;
    DataGlobals::WarmupFlag = false;
    DataEnvironment::DayOfYear_Schedule = General::OrdinalDay(Month, DayOfMonth, 1);
    ScheduleManager::UpdateScheduleValues();
    // Initialize zone areas and volumes - too many other things need to be set up to do these in the normal routines
    DataHeatBalance::Zone(1).FloorArea = 232.26;
    DataEnvironment::StdRhoAir = 1.225;
    DataHeatBalance::ZoneIntGain.allocate(1);

    SizingManager::GetOARequirements();
    GetOAControllerInputs(OutputFiles::getSingleton());
    using DataZoneEquipment::CalcDesignSpecificationOutdoorAir;

    // Setup performnace tables
    using namespace EnergyPlus::DataEnvironment;
    // process schedules
    ProcessScheduleInput(OutputFiles::getSingleton()); // read schedules
    UpdateScheduleValues();
    // Get Unitary system
    GetInputZoneHybridUnitaryAirConditioners(ErrorsFound);
    // All to get OA requiremetns
    GetOARequirements();

    EXPECT_FALSE(ErrorsFound);
    // Initialize unit
    InitZoneHybridUnitaryAirConditioners(1, 1);
    Model *pZoneHybridUnitaryAirConditioner = &HybridUnitaryAirConditioners::ZoneHybridUnitaryAirConditioner(1);
    // setup local variables for model inputs
    Real64 Tosa, Tra, Wra, Wosa, RHosa, RHra, DesignMinVR, Requestedheating, RequestedCooling, Requested_Humidification, Requested_Dehumidification;
    RHosa = 0;
    std::string TimeDate;
    int modenumber = 0;
    Real64 MsaRatio, OSAF;
    MsaRatio = OSAF = 1;

    Requestedheating = RequestedCooling = Requested_Humidification = Requested_Dehumidification = 0;

    // Scenario 2: high cooling larger system

    DesignMinVR = 1.622720855;       // Zone Hybrid Unitary HVAC Requested Outdoor Air Ventilation Mass Flow Rate
    Tra = 22.93929413;               // Zone Hybrid Unitary HVAC Return Air Temperature
    Tosa = 26.67733333;              // Zone Hybrid Unitary HVAC Outside Air Temperature
    RHra = 17.3042157;               // Zone Hybrid Unitary HVAC Return Air Relative Humidity
    RHosa = 13.1602401;              // Zone Hybrid Unitary HVAC Outside Air Relative Humidity
    Requestedheating = -122396.255;  // Watts (Zone Predicted Sensible Load to Heating Setpoint Heat Transfer Rate
    RequestedCooling = -58469.99445; // Watts (Zone Predicted Sensible Load to Cooling Setpoint Heat Transfer Rate
    // Equivalent to a Zone Predicted Sensible Load to Setpoint Heat Transfer Rate [W] of -58470 w.
    // A positive value indicates a heating load, a negative value indicates a cooling load.
    Requested_Humidification = Requested_Dehumidification = 0;
    Wra = PsyWFnTdbRhPb(Tra, RHra / 100, 101.325);
    Wosa = PsyWFnTdbRhPb(Tosa, RHosa / 100, 101.325);
    pZoneHybridUnitaryAirConditioner->InletTemp = Tra;
    pZoneHybridUnitaryAirConditioner->InletHumRat = Wra;
    pZoneHybridUnitaryAirConditioner->InletEnthalpy = PsyHFnTdbRhPb(Tra, RHra / 100, 101325, "test");
    pZoneHybridUnitaryAirConditioner->InletPressure = 101325;
    pZoneHybridUnitaryAirConditioner->InletRH = RHra / 100;
    pZoneHybridUnitaryAirConditioner->SecInletTemp = Tosa;
    pZoneHybridUnitaryAirConditioner->SecInletHumRat = Wosa;
    pZoneHybridUnitaryAirConditioner->SecInletEnthalpy = PsyHFnTdbRhPb(Tosa, RHosa / 100, 101325, "test");
    pZoneHybridUnitaryAirConditioner->SecInletPressure = 101325;
    pZoneHybridUnitaryAirConditioner->SecInletRH = RHosa / 100;
    pZoneHybridUnitaryAirConditioner->Initialize(1);
    pZoneHybridUnitaryAirConditioner->InitializeModelParams();
    pZoneHybridUnitaryAirConditioner->ScalingFactor = pZoneHybridUnitaryAirConditioner->ScalingFactor * 2;
    pZoneHybridUnitaryAirConditioner->ScaledSystemMaximumSupplyAirMassFlowRate =
        pZoneHybridUnitaryAirConditioner->ScaledSystemMaximumSupplyAirMassFlowRate * 2;
    pZoneHybridUnitaryAirConditioner->doStep(RequestedCooling, Requestedheating, Requested_Humidification, Requested_Dehumidification, DesignMinVR);

    // output results
    modenumber = pZoneHybridUnitaryAirConditioner->PrimaryMode;
    Real64 Tsa = pZoneHybridUnitaryAirConditioner->OutletTemp;
    Real64 Msa = pZoneHybridUnitaryAirConditioner->OutletMassFlowRate;
    // double Msa_setting0= (pZoneHybridUnitaryAirConditioner->CurrentOperatingSettings[0].Supply_Air_Mass_Flow_Rate);
    Real64 deliveredSC = pZoneHybridUnitaryAirConditioner->UnitSensibleCoolingRate;
    Real64 deliveredSH = pZoneHybridUnitaryAirConditioner->UnitSensibleHeatingRate;
    Real64 returnOSAF = pZoneHybridUnitaryAirConditioner->averageOSAF;
    // checks
    EXPECT_NEAR(1.0, returnOSAF, 0.001);
    EXPECT_GT(deliveredSC, 0);
    EXPECT_NEAR(0.0, deliveredSH, 0.001);
    EXPECT_LT(Tsa, Tra);
    EXPECT_GT(Msa, DesignMinVR);
}
TEST_F(EnergyPlusFixture, UnitaryHybridAirConditioner_OutsideEnvConditions)
{
    std::vector<std::string> snippet = getAllLinesInFile2(configured_source_directory() + "/tst/EnergyPlus/unit/UnitaryHybridUnitTest_DOSA.idf");
    std::string string = delimited_string(snippet);
    ASSERT_TRUE(process_idf(string));
    // setup environment
    bool ErrorsFound(false);
    GetZoneData(ErrorsFound);
    EXPECT_FALSE(ErrorsFound);
    // Initialize schedule values
    DataGlobals::TimeStep = 1;
    DataHVACGlobals::TimeStepSys = 1;
    DataGlobals::NumOfTimeStepInHour = 1;
    DataGlobals::MinutesPerTimeStep = 60;
    DataEnvironment::Month = 1;
    DataEnvironment::DayOfMonth = 21;
    DataGlobals::HourOfDay = 1;
    DataEnvironment::DSTIndicator = 0;
    DataEnvironment::DayOfWeek = 2;
    DataEnvironment::HolidayIndex = 0;
    DataGlobals::WarmupFlag = false;
    DataEnvironment::DayOfYear_Schedule = General::OrdinalDay(Month, DayOfMonth, 1);
    ScheduleManager::UpdateScheduleValues();
    // Initialize zone areas and volumes - too many other things need to be set up to do these in the normal routines
    DataHeatBalance::Zone(1).FloorArea = 232.26;
    DataEnvironment::StdRhoAir = 1.225;
    DataHeatBalance::ZoneIntGain.allocate(1);

    SizingManager::GetOARequirements();
    GetOAControllerInputs(OutputFiles::getSingleton());
    using DataZoneEquipment::CalcDesignSpecificationOutdoorAir;

    // Setup performnace tables
    using namespace EnergyPlus::DataEnvironment;
    // process schedules
    ProcessScheduleInput(OutputFiles::getSingleton()); // read schedules
    UpdateScheduleValues();
    // Get Unitary system
    GetInputZoneHybridUnitaryAirConditioners(ErrorsFound);
    // All to get OA requiremetns
    GetOARequirements();

    EXPECT_FALSE(ErrorsFound);
    // Initialize unit
    InitZoneHybridUnitaryAirConditioners(1, 1);
    Model *pZoneHybridUnitaryAirConditioner = &HybridUnitaryAirConditioners::ZoneHybridUnitaryAirConditioner(1);
    // setup local variables for model inputs
    Real64 Tosa, Tra, Wra, Wosa, RHosa, RHra, DesignMinVR, Requestedheating, RequestedCooling, Requested_Humidification, Requested_Dehumidification;
    RHosa = 0;
    std::string TimeDate;
    int modenumber = 0;
    Real64 MsaRatio, OSAF;
    MsaRatio = OSAF = 1;

    Requestedheating = RequestedCooling = Requested_Humidification = Requested_Dehumidification = 0;

    // Scenario 3: Outside of env conditions. should go to standby and have standby energy
    DesignMinVR = 1.622720855;       // Zone Hybrid Unitary HVAC Requested Outdoor Air Ventilation Mass Flow Rate
    Tra = 22.93929413;               // Zone Hybrid Unitary HVAC Return Air Temperature
    Tosa = 26.67733333;              // Zone Hybrid Unitary HVAC Outside Air Temperature
    RHra = 17.3042157;               // Zone Hybrid Unitary HVAC Return Air Relative Humidity
    RHosa = 13.1602401;              // Zone Hybrid Unitary HVAC Outside Air Relative Humidity
    Requestedheating = -122396.255;  // Watts (Zone Predicted Sensible Load to Heating Setpoint Heat Transfer Rate
    RequestedCooling = -58469.99445; // Watts (Zone Predicted Sensible Load to Cooling Setpoint Heat Transfer Rate
    // Equivalent to a Zone Predicted Sensible Load to Setpoint Heat Transfer Rate [W] of -58470 w.
    // A positive value indicates a heating load, a negative value indicates a cooling load.
    Requested_Humidification = Requested_Dehumidification = 0;
    Wra = PsyWFnTdbRhPb(Tra, RHra / 100, 101.325);
    Wosa = PsyWFnTdbRhPb(Tosa, RHosa / 100, 101.325);
    pZoneHybridUnitaryAirConditioner->InletTemp = Tra;
    pZoneHybridUnitaryAirConditioner->InletHumRat = Wra;
    pZoneHybridUnitaryAirConditioner->InletEnthalpy = PsyHFnTdbRhPb(Tra, RHra / 100, 101325, "test");
    pZoneHybridUnitaryAirConditioner->InletPressure = 101325;
    pZoneHybridUnitaryAirConditioner->InletRH = RHra / 100;
    pZoneHybridUnitaryAirConditioner->SecInletEnthalpy = PsyHFnTdbRhPb(Tosa, RHosa / 100, 101325, "test");
    pZoneHybridUnitaryAirConditioner->SecInletPressure = 101325;
    pZoneHybridUnitaryAirConditioner->SecInletRH = RHosa / 100;
    pZoneHybridUnitaryAirConditioner->Initialize(1);
    pZoneHybridUnitaryAirConditioner->InitializeModelParams();
    pZoneHybridUnitaryAirConditioner->SecInletTemp = 150;
    pZoneHybridUnitaryAirConditioner->SecInletHumRat = 0;

    pZoneHybridUnitaryAirConditioner->doStep(RequestedCooling, Requestedheating, Requested_Humidification, Requested_Dehumidification, DesignMinVR);
    modenumber = pZoneHybridUnitaryAirConditioner->PrimaryMode;
    // checks
    EXPECT_EQ(0, modenumber);
}

TEST_F(EnergyPlusFixture, UnitaryHybridAirConditioner_LowCooling)
{
    std::vector<std::string> snippet = getAllLinesInFile2(configured_source_directory() + "/tst/EnergyPlus/unit/UnitaryHybridUnitTest_DOSA.idf");
    std::string string = delimited_string(snippet);
    ASSERT_TRUE(process_idf(string));
    // setup environment
    bool ErrorsFound(false);
    GetZoneData(ErrorsFound);
    EXPECT_FALSE(ErrorsFound);
    // Initialize schedule values
    DataGlobals::TimeStep = 1;
    DataHVACGlobals::TimeStepSys = 1;
    DataGlobals::NumOfTimeStepInHour = 1;
    DataGlobals::MinutesPerTimeStep = 60;
    DataEnvironment::Month = 1;
    DataEnvironment::DayOfMonth = 21;
    DataGlobals::HourOfDay = 1;
    DataEnvironment::DSTIndicator = 0;
    DataEnvironment::DayOfWeek = 2;
    DataEnvironment::HolidayIndex = 0;
    DataGlobals::WarmupFlag = false;
    DataEnvironment::DayOfYear_Schedule = General::OrdinalDay(Month, DayOfMonth, 1);
    ScheduleManager::UpdateScheduleValues();
    // Initialize zone areas and volumes - too many other things need to be set up to do these in the normal routines
    DataHeatBalance::Zone(1).FloorArea = 232.26;
    DataEnvironment::StdRhoAir = 1.225;
    DataHeatBalance::ZoneIntGain.allocate(1);

    SizingManager::GetOARequirements();
    GetOAControllerInputs(OutputFiles::getSingleton());
    using DataZoneEquipment::CalcDesignSpecificationOutdoorAir;

    // Setup performnace tables
    using namespace EnergyPlus::DataEnvironment;
    // process schedules
    ProcessScheduleInput(OutputFiles::getSingleton()); // read schedules
    UpdateScheduleValues();
    // Get Unitary system
    GetInputZoneHybridUnitaryAirConditioners(ErrorsFound);
    // All to get OA requiremetns
    GetOARequirements();

    EXPECT_FALSE(ErrorsFound);
    // Initialize unit
    InitZoneHybridUnitaryAirConditioners(1, 1);
    Model *pZoneHybridUnitaryAirConditioner = &HybridUnitaryAirConditioners::ZoneHybridUnitaryAirConditioner(1);
    // setup local variables for model inputs
    Real64 Tosa, Tra, Wra, Wosa, RHosa, RHra, DesignMinVR, Requestedheating, RequestedCooling, Requested_Humidification, Requested_Dehumidification;
    RHosa = 0;
    std::string TimeDate;
    int modenumber = 0;
    Real64 MsaRatio, OSAF;
    MsaRatio = OSAF = 1;

    Requestedheating = RequestedCooling = Requested_Humidification = Requested_Dehumidification = 0;

    // Scenario 4: Low Cooling
    DesignMinVR = 1.622720855;
    Tra = 23.00655455; //
    Tosa = 26.67733333;
    RHra = 17.3791073;
    RHosa = 13.1602401;
    Requestedheating = -64358.68966; //-
    RequestedCooling = -633.6613591; // W
    // Equivalent to a Zone Predicted Sensible Load to Setpoint Heat Transfer Rate [W] of -58470 w.
    // A positive value indicates a heating load, a negative value indicates a cooling load.
    Requested_Humidification = Requested_Dehumidification = 0;
    Wra = PsyWFnTdbRhPb(Tra, RHra / 100, 101.325);
    Wosa = PsyWFnTdbRhPb(Tosa, RHosa / 100, 101.325);
    pZoneHybridUnitaryAirConditioner->InletTemp = Tra;
    pZoneHybridUnitaryAirConditioner->InletHumRat = Wra;
    pZoneHybridUnitaryAirConditioner->InletEnthalpy = PsyHFnTdbRhPb(Tra, RHra / 100, 101325, "test");
    pZoneHybridUnitaryAirConditioner->InletPressure = 101325;
    pZoneHybridUnitaryAirConditioner->InletRH = RHra / 100;
    pZoneHybridUnitaryAirConditioner->SecInletTemp = Tosa;
    pZoneHybridUnitaryAirConditioner->SecInletHumRat = Wosa;
    pZoneHybridUnitaryAirConditioner->SecInletEnthalpy = PsyHFnTdbRhPb(Tosa, RHosa / 100, 101325, "test");
    pZoneHybridUnitaryAirConditioner->SecInletPressure = 101325;
    pZoneHybridUnitaryAirConditioner->SecInletRH = RHosa / 100;
    pZoneHybridUnitaryAirConditioner->Initialize(1);
    pZoneHybridUnitaryAirConditioner->InitializeModelParams();

    /// add all the corre correct values to set in pZoneHybridUnitaryAirConditioner
    pZoneHybridUnitaryAirConditioner->SecInletTemp = Tosa;
    pZoneHybridUnitaryAirConditioner->SecInletHumRat = Wosa;
    pZoneHybridUnitaryAirConditioner->doStep(RequestedCooling, Requestedheating, Requested_Humidification, Requested_Dehumidification, DesignMinVR);

    // output results
    modenumber = pZoneHybridUnitaryAirConditioner->PrimaryMode;
    Real64 Tsa = pZoneHybridUnitaryAirConditioner->OutletTemp;
    Real64 deliveredSC = pZoneHybridUnitaryAirConditioner->UnitSensibleCoolingRate;
    Real64 deliveredSH = pZoneHybridUnitaryAirConditioner->UnitSensibleHeatingRate;
    Real64 returnOSAF = pZoneHybridUnitaryAirConditioner->averageOSAF;
    // checks
    EXPECT_NEAR(1.0, returnOSAF, 0.001);
    EXPECT_GT(deliveredSC, 0);
    EXPECT_NEAR(0.0, deliveredSH, 0.001);
    EXPECT_LT(Tsa, Tra);
}

TEST_F(EnergyPlusFixture, UnitaryHybridAirConditioner_NoHeatingCooling_MinVentilation)
{
    std::vector<std::string> snippet = getAllLinesInFile2(configured_source_directory() + "/tst/EnergyPlus/unit/UnitaryHybridUnitTest_DOSA.idf");
    std::string string = delimited_string(snippet);
    ASSERT_TRUE(process_idf(string));
    // setup environment
    bool ErrorsFound(false);
    GetZoneData(ErrorsFound);
    EXPECT_FALSE(ErrorsFound);
    // Initialize schedule values
    DataGlobals::TimeStep = 1;
    DataHVACGlobals::TimeStepSys = 1;
    DataGlobals::NumOfTimeStepInHour = 1;
    DataGlobals::MinutesPerTimeStep = 60;
    DataEnvironment::Month = 1;
    DataEnvironment::DayOfMonth = 21;
    DataGlobals::HourOfDay = 1;
    DataEnvironment::DSTIndicator = 0;
    DataEnvironment::DayOfWeek = 2;
    DataEnvironment::HolidayIndex = 0;
    DataGlobals::WarmupFlag = false;
    DataEnvironment::DayOfYear_Schedule = General::OrdinalDay(Month, DayOfMonth, 1);
    ScheduleManager::UpdateScheduleValues();
    // Initialize zone areas and volumes - too many other things need to be set up to do these in the normal routines
    DataHeatBalance::Zone(1).FloorArea = 232.26;
    DataEnvironment::StdRhoAir = 1.225;
    DataHeatBalance::ZoneIntGain.allocate(1);

    SizingManager::GetOARequirements();
    GetOAControllerInputs(OutputFiles::getSingleton());
    using DataZoneEquipment::CalcDesignSpecificationOutdoorAir;

    // Setup performance tables
    using namespace EnergyPlus::DataEnvironment;
    // process schedules
    ProcessScheduleInput(OutputFiles::getSingleton()); // read schedules
    UpdateScheduleValues();
    // Get Unitary system
    GetInputZoneHybridUnitaryAirConditioners(ErrorsFound);
    // All to get OA requirements
    GetOARequirements();

    EXPECT_FALSE(ErrorsFound);
    // Initialize unit
    InitZoneHybridUnitaryAirConditioners(1, 1);
    Model *pZoneHybridUnitaryAirConditioner = &HybridUnitaryAirConditioners::ZoneHybridUnitaryAirConditioner(1);
    // setup local variables for model inputs
    Real64 Tosa, Tra, Wra, Wosa, RHosa, RHra, DesignMinVR, Requestedheating, RequestedCooling, Requested_Humidification, Requested_Dehumidification;
    RHosa = 0;
    std::string TimeDate;
    int modenumber = 0;
    Real64 MsaRatio, OSAF;
    MsaRatio = OSAF = 1;

    Requestedheating = RequestedCooling = Requested_Humidification = Requested_Dehumidification = 0;

    // Scenario 5: No Heating or Cooling, Minimum Ventilation
    DesignMinVR = 1.622720855;
    Tra = 21.83325675;
    Tosa = 26.67733333;
    RHra = 18.894394;
    RHosa = 13.1602401;
    Wra = PsyWFnTdbRhPb(Tra, RHra / 100, 101.325);
    Wosa = PsyWFnTdbRhPb(Tosa, RHosa / 100, 101.325);
    Requestedheating = -55795.8058;
    RequestedCooling = 8171.47128;
    pZoneHybridUnitaryAirConditioner->InletTemp = Tra;
    pZoneHybridUnitaryAirConditioner->InletHumRat = Wra;
    pZoneHybridUnitaryAirConditioner->InletEnthalpy = PsyHFnTdbRhPb(Tra, RHra / 100, 101325, "test");
    pZoneHybridUnitaryAirConditioner->InletPressure = 101325;
    pZoneHybridUnitaryAirConditioner->InletRH = RHra / 100;
    pZoneHybridUnitaryAirConditioner->SecInletTemp = Tosa;
    pZoneHybridUnitaryAirConditioner->SecInletHumRat = Wosa;
    pZoneHybridUnitaryAirConditioner->SecInletEnthalpy = PsyHFnTdbRhPb(Tosa, RHosa / 100, 101325, "test");
    pZoneHybridUnitaryAirConditioner->SecInletPressure = 101325;
    pZoneHybridUnitaryAirConditioner->SecInletRH = RHosa / 100;
    pZoneHybridUnitaryAirConditioner->Initialize(1);
    pZoneHybridUnitaryAirConditioner->doStep(RequestedCooling, Requestedheating, Requested_Humidification, Requested_Dehumidification, DesignMinVR);

    // output results
    modenumber = pZoneHybridUnitaryAirConditioner->PrimaryMode;
    Real64 Tsa = pZoneHybridUnitaryAirConditioner->OutletTemp;
    Real64 Msa = pZoneHybridUnitaryAirConditioner->OutletMassFlowRate;
    Real64 Mreturn = pZoneHybridUnitaryAirConditioner->InletMassFlowRate;
    Real64 Mrelief = pZoneHybridUnitaryAirConditioner->SecOutletMassFlowRate;
    // checks
    EXPECT_NEAR(Tsa, Tosa, 1.0);
    EXPECT_NEAR(Msa, DesignMinVR, 0.001);
    EXPECT_NEAR(Mreturn, 0, 0.001);
    EXPECT_NEAR(Mrelief, 0, 0.001);

}

TEST_F(EnergyPlusFixture, UnitaryHybridAirConditioner_VentLoadCheck)
{
    std::vector<std::string> snippet = getAllLinesInFile2(configured_source_directory() + "/tst/EnergyPlus/unit/UnitaryHybridUnitTest_DOSA.idf");
    std::string string = delimited_string(snippet);
    ASSERT_TRUE(process_idf(string));
    // setup environment
    bool ErrorsFound(false);
    GetZoneData(ErrorsFound);
    EXPECT_FALSE(ErrorsFound);
    // Initialize schedule values
    DataGlobals::TimeStep = 1;
    DataHVACGlobals::TimeStepSys = 1;
    DataGlobals::NumOfTimeStepInHour = 1;
    DataGlobals::MinutesPerTimeStep = 60;
    DataEnvironment::Month = 1;
    DataEnvironment::DayOfMonth = 21;
    DataGlobals::HourOfDay = 1;
    DataEnvironment::DSTIndicator = 0;
    DataEnvironment::DayOfWeek = 2;
    DataEnvironment::HolidayIndex = 0;
    DataGlobals::WarmupFlag = false;
    DataEnvironment::DayOfYear_Schedule = General::OrdinalDay(Month, DayOfMonth, 1);
    ScheduleManager::UpdateScheduleValues();
    // Initialize zone areas and volumes - too many other things need to be set up to do these in the normal routines
    DataHeatBalance::Zone(1).FloorArea = 232.26;
    DataEnvironment::StdRhoAir = 1.225;
    DataHeatBalance::ZoneIntGain.allocate(1);

    NumOfZones = 1;
    ZoneSysEnergyDemand.allocate(NumOfZones);
    DeadBandOrSetback.allocate(NumOfZones);

    HeatBalanceManager::GetZoneData(ErrorsFound); // read zone data
    EXPECT_FALSE(ErrorsFound);                    // expect no errors
    DataZoneEquipment::GetZoneEquipmentData();    // read zone equipment    SystemReports::ReportMaxVentilationLoads();
    DataZoneEquipment::ZoneEquipInputsFilled = true;
    ZoneOAMassFlow.allocate(NumOfZones);
    ZoneOAMass.allocate(NumOfZones);
    ZoneOAVolFlowStdRho.allocate(NumOfZones);
    ZoneOAVolFlowCrntRho.allocate(NumOfZones);
    ZoneOAVolStdRho.allocate(NumOfZones);
    ZoneOAVolCrntRho.allocate(NumOfZones);
    ZoneMechACH.allocate(NumOfZones);
    MAT.allocate(NumOfZones);
    ZoneAirHumRatAvg.allocate(NumOfZones);
    MaxHeatingLoadMetByVent.allocate(NumOfZones);
    MaxOverheatingByVent.allocate(NumOfZones);
    MaxCoolingLoadMetByVent.allocate(NumOfZones);
    MaxOvercoolingByVent.allocate(NumOfZones);
    ZoneSysEnergyDemand(1).TotalOutputRequired = 58469.99445;
    DeadBandOrSetback(1) = false;
    ZoneEquipList(ZoneEquipConfig(1).EquipListIndex).EquipIndex(1) = 1;
    CreateEnergyReportStructure();

    SizingManager::GetOARequirements();
    GetOAControllerInputs(OutputFiles::getSingleton());
    using DataZoneEquipment::CalcDesignSpecificationOutdoorAir;

    // Setup performnace tables
    using namespace EnergyPlus::DataEnvironment;
    // process schedules
    ProcessScheduleInput(OutputFiles::getSingleton()); // read schedules
    UpdateScheduleValues();
    // Get Unitary system
    GetInputZoneHybridUnitaryAirConditioners(ErrorsFound);
    // All to get OA requirements
    GetOARequirements();

    EXPECT_FALSE(ErrorsFound);
    // Initialize unit
    InitZoneHybridUnitaryAirConditioners(1, 1);
    Model *pZoneHybridUnitaryAirConditioner = &HybridUnitaryAirConditioners::ZoneHybridUnitaryAirConditioner(1);
    // setup local variables for model inputs
    Real64 Tosa, Tra, Wra, Wosa, RHosa, RHra, DesignMinVR, Requestedheating, RequestedCooling, Requested_Humidification, Requested_Dehumidification;
    RHosa = 0;
    std::string TimeDate;
    Real64 MsaRatio, OSAF;
    MsaRatio = OSAF = 1;

    Requestedheating = RequestedCooling = Requested_Humidification = Requested_Dehumidification = 0;

    // Scenario 1: Hi Cooling

    DesignMinVR = 1.622720855;       // Zone Hybrid Unitary HVAC Requested Outdoor Air Ventilation Mass Flow Rate
    Tra = 22.93929413;               // Zone Hybrid Unitary HVAC Return Air Temperature
    Tosa = 26.67733333;              // Zone Hybrid Unitary HVAC Outside Air Temperature
    RHra = 17.3042157;               // Zone Hybrid Unitary HVAC Return Air Relative Humidity
    RHosa = 13.1602401;              // Zone Hybrid Unitary HVAC Outside Air Relative Humidity
    Requestedheating = -122396.255;  // Watts (Zone Predicted Sensible Load to Heating Setpoint Heat Transfer Rate
    RequestedCooling = -58469.99445; // Watts (Zone Predicted Sensible Load to Cooling Setpoint Heat Transfer Rate
    // Equivalent to a Zone Predicted Sensible Load to Setpoint Heat Transfer Rate [W] of -58470 w.
    // A positive value indicates a heating load, a negative value indicates a cooling load.
    Requested_Humidification = Requested_Dehumidification = 0;
    Wra = PsyWFnTdbRhPb(Tra, RHra / 100, 101325);
    Wosa = PsyWFnTdbRhPb(Tosa, RHosa / 100, 101325);
    pZoneHybridUnitaryAirConditioner->InletTemp = Tra;
    pZoneHybridUnitaryAirConditioner->InletHumRat = Wra;
    pZoneHybridUnitaryAirConditioner->InletEnthalpy = PsyHFnTdbRhPb(Tra, RHra / 100, 101325, "test");
    pZoneHybridUnitaryAirConditioner->InletPressure = 101325;
    pZoneHybridUnitaryAirConditioner->InletRH = RHra / 100;
    pZoneHybridUnitaryAirConditioner->SecInletMassFlowRate = DesignMinVR;
    pZoneHybridUnitaryAirConditioner->SecInletTemp = Tosa;
    pZoneHybridUnitaryAirConditioner->SecInletHumRat = Wosa;
    pZoneHybridUnitaryAirConditioner->SecInletEnthalpy = PsyHFnTdbRhPb(Tosa, RHosa / 100, 101325, "test");
    pZoneHybridUnitaryAirConditioner->SecInletPressure = 101325;
    pZoneHybridUnitaryAirConditioner->SecInletRH = RHosa / 100;
    pZoneHybridUnitaryAirConditioner->doStep(RequestedCooling, Requestedheating, Requested_Humidification, Requested_Dehumidification, DesignMinVR);
    ReportZoneHybridUnitaryAirConditioners(1);

    ZoneHybridUnitaryAirConditioner(1).InletTemp = Tra;
    ZoneHybridUnitaryAirConditioner(1).SecInletTemp = Tosa;
    SystemReports::ReportMaxVentilationLoads();
    // output results
    Real64 ovr_htg_vent_load = MaxOverheatingByVent(1);
    Real64 ovr_clg_vent_load = MaxOvercoolingByVent(1);
    // checks
    EXPECT_GT(ovr_htg_vent_load, 0); // add heating ventilation load from outside air
    EXPECT_EQ(ovr_clg_vent_load, 0);
}

TEST_F(EnergyPlusFixture, UnitaryHybridAirConditioner_AvailabilityManagerOff)
{
    std::vector<std::string> snippet = getAllLinesInFile2(configured_source_directory() + "/tst/EnergyPlus/unit/UnitaryHybridUnitTest_DOSA.idf");
    std::string string = delimited_string(snippet);
    ASSERT_TRUE(process_idf(string));
    // setup environment
    bool ErrorsFound(false);
    GetZoneData(ErrorsFound);
    EXPECT_FALSE(ErrorsFound);
    // Initialize schedule values
    DataGlobals::TimeStep = 1;
    DataHVACGlobals::TimeStepSys = 1;
    DataGlobals::NumOfTimeStepInHour = 1;
    DataGlobals::MinutesPerTimeStep = 60;
    DataEnvironment::Month = 1;
    DataEnvironment::DayOfMonth = 21;
    DataGlobals::HourOfDay = 1;
    DataEnvironment::DSTIndicator = 0;
    DataEnvironment::DayOfWeek = 2;
    DataEnvironment::HolidayIndex = 0;
    DataGlobals::WarmupFlag = false;
    DataEnvironment::DayOfYear_Schedule = General::OrdinalDay(Month, DayOfMonth, 1);
    ScheduleManager::UpdateScheduleValues();
    // Initialize zone areas and volumes - too many other things need to be set up to do these in the normal routines
    DataHeatBalance::Zone(1).FloorArea = 232.26;
    DataEnvironment::StdRhoAir = 1.225;
    DataHeatBalance::ZoneIntGain.allocate(1);

    SizingManager::GetOARequirements();
    GetOAControllerInputs(OutputFiles::getSingleton());
    using DataZoneEquipment::CalcDesignSpecificationOutdoorAir;

    // Setup performance tables
    using namespace EnergyPlus::DataEnvironment;
    // process schedules
    ProcessScheduleInput(OutputFiles::getSingleton()); // read schedules
    UpdateScheduleValues();
    // Get Unitary system
    GetInputZoneHybridUnitaryAirConditioners(ErrorsFound);
    // All to get OA requirements
    GetOARequirements();

    EXPECT_FALSE(ErrorsFound);
    // Initialize unit
    InitZoneHybridUnitaryAirConditioners(1, 1);
    Model *pZoneHybridUnitaryAirConditioner = &HybridUnitaryAirConditioners::ZoneHybridUnitaryAirConditioner(1);
    // setup local variables for model inputs
    Real64 Tosa, Tra, Wra, Wosa, RHosa, RHra, DesignMinVR, Requestedheating, RequestedCooling, Requested_Humidification, Requested_Dehumidification;
    RHosa = 0;
    std::string TimeDate;
    int modenumber = 0;
    Real64 MsaRatio, OSAF;
    MsaRatio = OSAF = 1;

    Requestedheating = RequestedCooling = Requested_Humidification = Requested_Dehumidification = 0;

    // Scenario 6: Availability Manager Off
    DesignMinVR = 1.622720855;       // Zone Hybrid Unitary HVAC Requested Outdoor Air Ventilation Mass Flow Rate
    Tra = 22.93929413;               // Zone Hybrid Unitary HVAC Return Air Temperature
    Tosa = 26.67733333;              // Zone Hybrid Unitary HVAC Outside Air Temperature
    RHra = 17.3042157;               // Zone Hybrid Unitary HVAC Return Air Relative Humidity
    RHosa = 13.1602401;              // Zone Hybrid Unitary HVAC Outside Air Relative Humidity
    Requestedheating = -122396.255;  // Watts (Zone Predicted Sensible Load to Heating Setpoint Heat Transfer Rate
    RequestedCooling = -58469.99445; // Watts (Zone Predicted Sensible Load to Cooling Setpoint Heat Transfer Rate
    Tra = 21.83325675;
    Tosa = 26.67733333;
    RHra = 18.894394;
    RHosa = 13.1602401;
    Wra = PsyWFnTdbRhPb(Tra, RHra / 100, 101.325);
    Wosa = PsyWFnTdbRhPb(Tosa, RHosa / 100, 101.325);
    pZoneHybridUnitaryAirConditioner->AvailStatus = 1;
    pZoneHybridUnitaryAirConditioner->InletTemp = Tra;
    pZoneHybridUnitaryAirConditioner->InletHumRat = Wra;
    pZoneHybridUnitaryAirConditioner->InletEnthalpy = PsyHFnTdbRhPb(Tra, RHra / 100, 101325, "test");
    pZoneHybridUnitaryAirConditioner->InletPressure = 101325;
    pZoneHybridUnitaryAirConditioner->InletRH = RHra / 100;
    pZoneHybridUnitaryAirConditioner->SecInletTemp = Tosa;
    pZoneHybridUnitaryAirConditioner->SecInletHumRat = Wosa;
    pZoneHybridUnitaryAirConditioner->SecInletEnthalpy = PsyHFnTdbRhPb(Tosa, RHosa / 100, 101325, "test");
    pZoneHybridUnitaryAirConditioner->SecInletPressure = 101325;
    pZoneHybridUnitaryAirConditioner->SecInletRH = RHosa / 100;
    pZoneHybridUnitaryAirConditioner->Initialize(1);
    pZoneHybridUnitaryAirConditioner->doStep(RequestedCooling, Requestedheating, Requested_Humidification, Requested_Dehumidification, DesignMinVR);

    // output results
    modenumber = pZoneHybridUnitaryAirConditioner->PrimaryMode;
    Real64 Msa = pZoneHybridUnitaryAirConditioner->OutletMassFlowRate;
    Real64 deliveredSC = pZoneHybridUnitaryAirConditioner->UnitSensibleCoolingRate;

   // checks
    EXPECT_EQ(modenumber, 0);
    EXPECT_EQ(Msa, 0);
    EXPECT_EQ(deliveredSC, 0);

}

TEST_F(EnergyPlusFixture, UnitaryHybridAirConditioner_MeterAndReport_test) {
    std::vector<std::string> snippet = getAllLinesInFile2(
            configured_source_directory() + "/tst/EnergyPlus/unit/UnitaryHybridUnitTest_DOSA.idf");
    std::string string = delimited_string(snippet);
    ASSERT_TRUE(process_idf(string));
    // setup environment
    bool ErrorsFound(false);
    GetZoneData(ErrorsFound);
    EXPECT_FALSE(ErrorsFound);
    // Initialize schedule values
    DataGlobals::TimeStep = 1;
    DataHVACGlobals::TimeStepSys = 1;
    DataGlobals::NumOfTimeStepInHour = 1;
    DataGlobals::MinutesPerTimeStep = 60;
    DataEnvironment::Month = 1;
    DataEnvironment::DayOfMonth = 21;
    DataGlobals::HourOfDay = 1;
    DataEnvironment::DSTIndicator = 0;
    DataEnvironment::DayOfWeek = 2;
    DataEnvironment::HolidayIndex = 0;
    DataGlobals::WarmupFlag = false;
    DataEnvironment::DayOfYear_Schedule = General::OrdinalDay(Month, DayOfMonth, 1);
    ScheduleManager::UpdateScheduleValues();
    // Initialize zone areas and volumes - too many other things need to be set up to do these in the normal routines
    DataHeatBalance::Zone(1).FloorArea = 232.26;
    DataEnvironment::StdRhoAir = 1.225;
    DataHeatBalance::ZoneIntGain.allocate(1);

    SizingManager::GetOARequirements();
    GetOAControllerInputs(OutputFiles::getSingleton());
    using DataZoneEquipment::CalcDesignSpecificationOutdoorAir;

    // Setup performnace tables
    using namespace EnergyPlus::DataEnvironment;
    // process schedules
    ProcessScheduleInput(OutputFiles::getSingleton()); // read schedules
    UpdateScheduleValues();
    // Get Unitary system
    GetInputZoneHybridUnitaryAirConditioners(ErrorsFound);
    // All to get OA requirements
    GetOARequirements();

    EXPECT_FALSE(ErrorsFound);
    // Initialize unit
    InitZoneHybridUnitaryAirConditioners(1, 1);
    Model *pZoneHybridUnitaryAirConditioner = &HybridUnitaryAirConditioners::ZoneHybridUnitaryAirConditioner(1);
    // setup local variables for model inputs
    Real64 RHosa, Requestedheating, RequestedCooling, Requested_Humidification, Requested_Dehumidification;
    RHosa = 0;
    std::string TimeDate;
    Real64 MsaRatio, OSAF, MaxFlow;
    MsaRatio = OSAF = 1;

    Requestedheating = RequestedCooling = Requested_Humidification = Requested_Dehumidification = 0;

    int NumFound;

    std::string TypeOfComp = "ZoneHVAC:HybridUnitaryHVAC";
    std::string NameOfComp = pZoneHybridUnitaryAirConditioner->Name;
    int NumVariables = GetNumMeteredVariables(TypeOfComp, NameOfComp);
    Array1D_int VarIndexes(NumVariables);                     // Variable Numbers
    Array1D_int VarTypes(NumVariables);                       // Variable Types (1=integer, 2=real, 3=meter)
    Array1D<OutputProcessor::TimeStepType> IndexTypes(
            NumVariables);                     // Variable Index Types (1=Zone,2=HVAC)
    Array1D<OutputProcessor::Unit> unitsForVar(NumVariables); // units from enum for each variable
    Array1D_int ResourceTypes(NumVariables);                  // ResourceTypes for each variable
    Array1D_string EndUses(NumVariables);                     // EndUses for each variable
    Array1D_string Groups(NumVariables);                      // Groups for each variable
    Array1D_string Names(NumVariables);                       // Variable Names for each variable

    GetMeteredVariables(TypeOfComp, NameOfComp, VarIndexes, VarTypes, IndexTypes, unitsForVar, ResourceTypes,
                        EndUses, Groups, Names, NumFound);

    // output results
    MaxFlow = pZoneHybridUnitaryAirConditioner->ScaledSystemMaximumSupplyAirVolumeFlowRate;

    // Check the meters associated with the ZoneHVAC:HybridUnitaryHVAC ouputs
    EXPECT_EQ(7, NumFound);
    EXPECT_EQ(ResourceTypes(1), 1010); // ENERGYTRANSFER - Cooling
    EXPECT_EQ(EndUses(1), "COOLINGCOILS");
    EXPECT_EQ(Groups(1), "HVAC");
    EXPECT_EQ(ResourceTypes(2), 1010); // ENERGYTRANSFER - Heating
    EXPECT_EQ(EndUses(2), "HEATINGCOILS");
    EXPECT_EQ(Groups(2), "HVAC");
    EXPECT_EQ(ResourceTypes(3), 1001); // ELECTRIC - Cooling Energy
    EXPECT_EQ(EndUses(3), "COOLING");
    EXPECT_EQ(Groups(3), "HVAC");
    EXPECT_EQ(ResourceTypes(4), 1001); // ELECTRIC - Fan Energy
    EXPECT_EQ(EndUses(4), "FANS");
    EXPECT_EQ(Groups(4), "HVAC");
    EXPECT_EQ(ResourceTypes(5), 1002); // NATURALGAS - Secondary Fuel Type - specified in UnitaryHybridUnitTest_DOSA.idf
    EXPECT_EQ(EndUses(5), "COOLING");
    EXPECT_EQ(Groups(5), "HVAC");
    EXPECT_EQ(ResourceTypes(6), 1012); // DISTRICTCOOLING - Third Fuel Type - specified in UnitaryHybridUnitTest_DOSA.idf
    EXPECT_EQ(EndUses(6), "COOLING");
    EXPECT_EQ(Groups(6), "HVAC");
    EXPECT_EQ(ResourceTypes(7), 1009); // WATER - Cooling Water Use
    EXPECT_EQ(EndUses(7), "COOLING");
    EXPECT_EQ(Groups(7), "HVAC");

    // Check that unit is included in Component Sizing Summary Report
    EXPECT_EQ("ZoneHVAC:HybridUnitaryHVAC", OutputReportPredefined::CompSizeTableEntry(1).typeField);
    EXPECT_EQ("MUNTERSEPX5000", OutputReportPredefined::CompSizeTableEntry(1).nameField);
    EXPECT_EQ("Scaled Maximum Supply Air Volume Flow Rate [m3/s]", OutputReportPredefined::CompSizeTableEntry(1).description);
    EXPECT_EQ(MaxFlow, OutputReportPredefined::CompSizeTableEntry(1).valField);

}

} // namespace EnergyPlus
