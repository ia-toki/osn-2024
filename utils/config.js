// Insert problem config.json in the config variable, and run this script on
// the browser console while the browser is showing the Judgels Problem Grading
// Config page after the test data files are configured (i.e. after pressing the
// "Configure test data files in tcframe format" button).

config = {};

_DEFAULT_JUDGELS_SUBTASKS = 10;
var numberOfSubtasks = Math.max(_DEFAULT_JUDGELS_SUBTASKS,
                                config.test_groups.length);

function getSampleInputName(sample, subtask) {
  return 'sampleTestCaseSubtaskIds[' + sample + '][' + subtask + ']';
}

function getTestGroupInputName(test_group, subtask) {
  return 'testGroupSubtaskIds[' + test_group + '][' + subtask + ']';
}

function getSubtaskPointsInputName(subtask) {
  return 'subtaskPoints[' + subtask + ']';
}

function fillTimeAndMemoryLimitValues() {
  $('input[name="timeLimit"]').val(config.time_limit * 1000);
  $('input[name="memoryLimit"]').val(config.memory_limit * 1024);
}

function fillSampleCasesSubtasksAllocation() {
  const allInputs = document.querySelectorAll('input[name=sampleTestCaseSubtaskIds]');
  for (var sample = 1; sample <= config.samples.length; ++sample) {
    const curSample = allInputs[sample];
    const curSet =  config.samples[sample - 1].toString();
    curSample.setAttribute("value", curSet)
  }
}

function fillTestGroupsSubtasksAllocation() {
  const allInputs = document.querySelectorAll('input[name=testGroupSubtaskIds]');
  for (var test_group = 1; test_group <= config.test_groups.length; ++test_group) {
    allInputs[test_group].setAttribute("value", config.test_groups[test_group - 1].toString())
  }
}

function fillSubtasksPoints() {
  const allInputs = document.querySelectorAll('input[name=subtaskPoints]');
  for (var subtask = 0; subtask < allInputs.length; ++subtask) {
    let curval = "";
    if(subtask < config.points.length) {
      curval = config.points[subtask].toString()
    }
    allInputs[subtask].setAttribute("value", curval);
  }
}

function fillCommunicator() {
  $('select[name="communicator"]').val("communicator.cpp");
}

function fillCustomScorer() {
  $('select[name="customScorer"]').val("scorer.cpp");
}

fillTimeAndMemoryLimitValues();
fillSampleCasesSubtasksAllocation();
fillTestGroupsSubtasksAllocation();
fillSubtasksPoints();

if (config.interactive) {
  fillCommunicator();
} else {
  // fillCustomScorer();
}