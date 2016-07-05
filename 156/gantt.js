// to edit the width of the gantt chart, open "media/jquery.ganttView.css"

var ganttData = [
	{
		id: 1, name: "Project Planning", series: [
			{ name: "Planned", start: new Date(2016,04,26), end: new Date(2016,04,30) },
			{ name: "Actual", start: new Date(2016,04,26), end: new Date(2016,04,31), color: "#88e4ff" }
		]
	}, 
	{
		id: 2, name: "Electronics Design", series: [
			{ name: "Planned", start: new Date(2016,04,27), end: new Date(2016,05,03) },
			{ name: "Actual", start: new Date(2016,04,30), end: new Date(2016,05,09), color: "#88e4ff" },
//			{ name: "Projected", start: new Date(2016,05,06), end: new Date(2016,05,17), color: "#e0e0e0" }
		]
	}, 
	{
		id: 3, name: "Testing of Electronics", series: [
			{ name: "Planned", start: new Date(2016,05,01), end: new Date(2016,05,03) },
			{ name: "Actual", start: new Date(2016,05,09), end: new Date(2016,05,16), color: "#88e4ff" }
		]
	}, 
	{
		id: 4, name: "Mechanical Fabrication", series: [
			{ name: "Planned", start: new Date(2016,05,09), end: new Date(2016,05,15) },
			{ name: "Actual", start: new Date(2016,05,14), end: new Date(2016,05,16), color: "#88e4ff" }
		]
	},
	{
		id: 5, name: "Assembly & Testing", series: [
			{ name: "Planned", start: new Date(2016,05,15), end: new Date(2016,05,17) },
			{ name: "Actual", start: new Date(2016,05,16), end: new Date(2016,05,17), color: "#88e4ff" }
		]
	}, 
	{
		id: 6, name: "Documentation", series: [
			{ name: "Planned", start: new Date(2016,05,01), end: new Date(2016,05,21) },
			{ name: "Documenting processes", start: new Date(2016,05,01), end: new Date(2016,05,21), color: "#88e4ff" },
			{ name: "Cleaning up website ", start: new Date(2016,05,27), end: new Date(2016,06,08), color: "#88e4ff" }
		]
	}, 
	{
		id: 7, name: "Presentation of Final Project", series: [
			{ name: "Planned", start: new Date(2016,05,22), end: new Date(2016,05,22) }
		]
	}, 
	{
		id: 8, name: "Refining the project", series: [
			{ name: "Actual", start: new Date(2016,05,23), end: new Date(2016,06,08), color: "#88e4ff" }
		]
	}

];