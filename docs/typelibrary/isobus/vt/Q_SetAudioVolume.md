# Q_SetAudioVolume

Command SetAudioVolume. 

ISO 11783-6

<p>This command can be used to control the audio on the VT (volume) ( Part 6 - F.12 )</p>

<p>Return values</p>

<p>iso_s16</p>

<ul>
	<li><span style="color:#0066cc">E_NO_ERR</span> - OK</li>
	<li><span style="color:#0066cc">E_OVERFLOW</span> - Buffer overflow</li>
	<li><span style="color:#0066cc">E_NOACT</span> - Command not possible in current state</li>
	<li><span style="color:#0066cc">E_NOT_AVAILABLE</span> - VT has got no adjustable volume output</li>
	<li><span style="color:#0066cc">E_NO_INSTANCE</span> - No VT client available</li>
</ul>
