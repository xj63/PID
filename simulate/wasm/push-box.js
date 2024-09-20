var forcePushBox = 23.6;

(async () => {
  async function waitInitModule() {
    return new Promise((resolve) => {
      Module.onRuntimeInitialized = resolve;
    });
  }

  await waitInitModule();
  const push_box = Module.cwrap("push_box", "number", [
    "number",
    "number",
    "number",
  ]);

  class PushBox {
    constructor() {
      this.speed = new Float32Array(1);
      this.speed[0] = 0.0;
      this.speed_ptr = Module._malloc(this.speed.length * this.speed.BYTES_PER_ELEMENT);
      Module.HEAPF32.set(this.speed, this.speed_ptr >> 2);

      // registry FinalizationRegistry to auto free speed memory.
      PushBox.registry.register(this, this.speed_ptr);
    }

    push(force, time) {
      push_box(this.speed_ptr, force, time);
      this.speed[0] = Module.HEAPF32[this.speed_ptr >> 2];
      return this.speed[0];
    }
  }

  // FinalizationRegistry free speed memory
  PushBox.registry = new FinalizationRegistry((ptr) => Module._free(ptr));

  // var box = new PushBox();
  // var updatedSpeed = box.push(10.0, 200000.0);
  // console.log("Updated Speed:", updatedSpeed);

  function DrawGraph() {
    var chartDom = document.getElementById('chart-container');
    var myChart = echarts.init(chartDom, null, { renderer: 'canvas', useDirtyRect: false });

    function genData(time = new Date(), speed = 0) {
      return {
        name: time.toString(),
        value: [time.getTime(), speed]
      };
    }

    function last1kDataWithoutMoving() {
      const now = new Date();
      return Array.from({ length: 150 }, (_, i) => genData(new Date(now - i * 30))).reverse();
    }

    let data = last1kDataWithoutMoving();
    var option = {
      title: { text: 'Push Box Speed' },
      tooltip: {
        trigger: 'axis',
        axisPointer: { animation: false }
      },
      xAxis: {
        type: 'time',
        splitLine: { show: false }
      },
      yAxis: {
        type: 'value',
        splitLine: { show: false }
      },
      series: [{
        name: 'Speed',
        type: 'line',
        showSymbol: false,
        data: data
      }]
    };

    const box = new PushBox();
    setInterval(() => {
      data.shift();
      var now = new Date();
      var dt = (now - data[data.length - 1].value[0]) / 1000.0;
      data.push(genData(now, box.push(forcePushBox, dt)));
      myChart.setOption({
        series: [{ data: data }]
      });
    }, 200);

    if (option && typeof option === 'object') myChart.setOption(option);
    window.addEventListener('resize', myChart.resize);
  }
  DrawGraph();

  function traceslider() {
    const slider = document.getElementById("slider");
    const sliderValue = document.getElementById("sliderValue");

    forcePushBox = slider.value;
    slider.addEventListener("input", () => {
      sliderValue.textContent = slider.value;
      forcePushBox = slider.value;
    });
  }
  traceslider();
})()
