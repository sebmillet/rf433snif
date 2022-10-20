data = """
050     356,   360
051     356,   360
052     356,   360
053     352,   360
054     352,   360
055     356,   360
056     356,   360
057     356,   360
058     356,   360
059     352,  3240
060     356,   356
061     356,   716
062     364,   352
063     360,   352
064     716,   364
065     352,   716
066     364,   352
067     716,   360
068     352,   376
069     340,   360
070     352,   716
071     716,   712
072     364,   352
073     364,   352
074     360,   344
075     364,   352
076     364,   352
077     712,   364
078     352,   716
079     360,   352
080     716,   716
081     360,   352
082     716,   716
083     712,   720
084     360,   352
085     364,   352
086     364,   352
087     360,   352
088     716,   716
089     360,   352
090     716,   716
091     712,   716
092     716,   716
093     716,   716
094     712,   716
095     364,   352
096     712,   372
097     340,   716
098     716,   720
099     712,   716
100    1076,103508
101     356,   360
102     360,   360
103     356,   360
104     356,   360
105     356,   360
106     356,   360
107     352,   360
108     356,   352
109     352,   360
110     356,  3240
111     356,   356
112     356,   716
113     364,   352
114     360,   352
115     716,   364
116     352,   712
117     364,   352
118     716,   360
119     352,   372
120     344,   360
121     352,   716
122     716,   716
123     364,   352
124     364,   352
125     360,   352
126     364,   352
127     364,   352
128     712,   360
129     352,   716
130     360,   352
131     716,   716
132     360,   352
133     716,   716
134     712,   720
135     360,   352
136     364,   352
137     364,   352
138     360,   352
139     716,   716
140     360,   352
141     716,   716
142     712,   720
143     716,   716
144     716,   716
145     716,   716
146     364,   352
147     712,   376
148     340,   712
149     716,   716
150     716,   716
151    1076,129080
152     356,   360
153     356,   360
154     352,   360
155     356,   360
156     352,   360
157     356,   360
158     352,   360
159     356,   360
160     352,   360
161     352,  3240
162     356,   360
163     356,   716
164     364,   352
165     360,   352
166     716,   364
167     352,   712
168     364,   352
169     716,   360
170     352,   376
171     340,   360
172     352,   716
173     716,   712
174     364,   352
175     356,   352
176     360,   352
177     364,   352
178     364,   352
179     716,   364
180     352,   716
181     360,   352
182     716,   716
183     360,   352
184     716,   716
185     712,   716
186     360,   352
187     364,   352
188     364,   352
189     360,   352
190     716,   720
191     360,   352
192     716,   716
193     716,   716
194     716,   712
195     716,   716
196     716,   716
197     364,   352
198     712,   372
199     344,   712
200     716,   716
201     712,   716
202    1076,154680
"""

data = [list(map(int, ( l.split()))) for l in data.strip().replace(',', ' ').split("\n")] 

data = list(zip(*list(zip(*data))[1:])) # remove 1st column

xy = [[0,0]]
t=0

for h,l in data:
   xy.append([t,1])
   t+=h
   xy.append([t,1])
   xy.append([t,0])
   t+=l
   xy.append([t,0])

import matplotlib.pyplot as plt 

plt.plot(*zip(*xy))
plt.show()
