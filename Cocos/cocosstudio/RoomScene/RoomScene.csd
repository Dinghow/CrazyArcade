<GameFile>
  <PropertyGroup Name="RoomScene" Type="Scene" ID="25b40bd2-9651-4d99-8001-b605be0de587" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Scene" Tag="5" ctype="GameNodeObjectData">
        <Size X="800.0000" Y="600.0000" />
        <Children>
          <AbstractNodeData Name="background" ActionTag="-1154451902" Tag="6" IconVisible="False" LeftMargin="0.0001" RightMargin="-0.0001" TopMargin="1.2775" BottomMargin="-1.2775" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" LeftEage="263" RightEage="263" TopEage="198" BottomEage="198" Scale9OriginX="263" Scale9OriginY="198" Scale9Width="273" Scale9Height="204" ctype="PanelObjectData">
            <Size X="800.0000" Y="600.0000" />
            <Children>
              <AbstractNodeData Name="confirm_button" ActionTag="311642469" Tag="7" IconVisible="False" LeftMargin="497.0792" RightMargin="179.9208" TopMargin="516.6882" BottomMargin="43.3118" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="93" Scale9Height="18" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="123.0000" Y="40.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="558.5792" Y="63.3118" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.6982" Y="0.1055" />
                <PreSize X="0.1538" Y="0.0667" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Normal" Path="RoomScene/confirm_pressed.png" Plist="" />
                <NormalFileData Type="Normal" Path="RoomScene/confirm_released.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="exit_button" Visible="False" ActionTag="1652448698" Tag="8" IconVisible="False" LeftMargin="629.3065" RightMargin="45.6935" TopMargin="516.6882" BottomMargin="44.3118" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="95" Scale9Height="17" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="125.0000" Y="39.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="691.8065" Y="63.8118" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.8648" Y="0.1064" />
                <PreSize X="0.1563" Y="0.0650" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Normal" Path="RoomScene/exit_pressed.png" Plist="" />
                <NormalFileData Type="Normal" Path="RoomScene/exit_released.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="m_list_view" ActionTag="-1939825862" Tag="9" IconVisible="False" LeftMargin="80.3715" RightMargin="539.6285" TopMargin="45.3940" BottomMargin="354.6060" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ScrollDirectionType="0" ItemMargin="5" DirectionType="Vertical" HorizontalType="Align_HorizontalCenter" ctype="ListViewObjectData">
                <Size X="180.0000" Y="200.0000" />
                <Children>
                  <AbstractNodeData Name="map_item1" ActionTag="-736100116" Tag="17" IconVisible="False" BottomMargin="160.0000" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                    <Size X="180.0000" Y="40.0000" />
                    <Children>
                      <AbstractNodeData Name="m_text1" ActionTag="-1554236909" Tag="20" IconVisible="False" LeftMargin="1.5220" RightMargin="92.4780" TopMargin="7.7140" BottomMargin="10.2860" FontSize="20" LabelText="Forest_1" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="86.0000" Y="22.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="44.5220" Y="21.2860" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="0" />
                        <PrePosition X="0.2473" Y="0.5321" />
                        <PreSize X="0.4778" Y="0.5500" />
                        <FontResource Type="Normal" Path="Font/CornDog.ttf" Plist="" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="m_check_box1" ActionTag="1551944637" Tag="23" IconVisible="False" LeftMargin="105.9700" RightMargin="33.0300" TopMargin="-3.9981" BottomMargin="1.9981" TouchEnable="True" ctype="CheckBoxObjectData">
                        <Size X="41.0000" Y="42.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="126.4700" Y="22.9981" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.7026" Y="0.5750" />
                        <PreSize X="0.2278" Y="1.0500" />
                        <NormalBackFileData Type="Normal" Path="RoomScene/checkbox_upSkin.png" Plist="" />
                        <PressedBackFileData Type="Normal" Path="RoomScene/checkbox_selectedSkin.png" Plist="" />
                        <NodeNormalFileData Type="Normal" Path="RoomScene/checkbox_selectedSkin.png" Plist="" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint />
                    <Position Y="160.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition Y="0.8000" />
                    <PreSize X="1.0000" Y="0.2000" />
                    <SingleColor A="255" R="150" G="200" B="255" />
                    <FirstColor A="255" R="150" G="200" B="255" />
                    <EndColor A="255" R="255" G="255" B="255" />
                    <ColorVector ScaleY="1.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="map_item2" ActionTag="-1146913570" ZOrder="1" Tag="24" IconVisible="False" TopMargin="45.0000" BottomMargin="115.0000" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                    <Size X="180.0000" Y="40.0000" />
                    <Children>
                      <AbstractNodeData Name="m_text2" ActionTag="-1096361071" Tag="25" IconVisible="False" LeftMargin="16.5220" RightMargin="107.4780" TopMargin="7.7140" BottomMargin="10.2860" FontSize="20" LabelText="Ice_2" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="56.0000" Y="22.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="44.5220" Y="21.2860" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="0" />
                        <PrePosition X="0.2473" Y="0.5321" />
                        <PreSize X="0.3111" Y="0.5500" />
                        <FontResource Type="Normal" Path="Font/CornDog.ttf" Plist="" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="m_check_box2" ActionTag="1842219516" Tag="26" IconVisible="False" LeftMargin="105.9700" RightMargin="33.0300" TopMargin="-3.9981" BottomMargin="1.9981" TouchEnable="True" ctype="CheckBoxObjectData">
                        <Size X="41.0000" Y="42.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="126.4700" Y="22.9981" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.7026" Y="0.5750" />
                        <PreSize X="0.2278" Y="1.0500" />
                        <NormalBackFileData Type="Normal" Path="RoomScene/checkbox_upSkin.png" Plist="" />
                        <PressedBackFileData Type="Normal" Path="RoomScene/checkbox_selectedSkin.png" Plist="" />
                        <NodeNormalFileData Type="Normal" Path="RoomScene/checkbox_selectedSkin.png" Plist="" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint />
                    <Position Y="115.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition Y="0.5750" />
                    <PreSize X="1.0000" Y="0.2000" />
                    <SingleColor A="255" R="150" G="200" B="255" />
                    <FirstColor A="255" R="150" G="200" B="255" />
                    <EndColor A="255" R="255" G="255" B="255" />
                    <ColorVector ScaleY="1.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="map_item3" ActionTag="-1616163978" ZOrder="2" Tag="25" IconVisible="False" TopMargin="90.0000" BottomMargin="70.0000" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                    <Size X="180.0000" Y="40.0000" />
                    <Children>
                      <AbstractNodeData Name="m_text3" ActionTag="1006532283" Tag="26" IconVisible="False" LeftMargin="-7.4780" RightMargin="83.4780" TopMargin="-3.2860" BottomMargin="-0.7140" FontSize="20" LabelText="Factory_3&#xA;" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="104.0000" Y="44.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="44.5220" Y="21.2860" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="0" />
                        <PrePosition X="0.2473" Y="0.5321" />
                        <PreSize X="0.5778" Y="1.1000" />
                        <FontResource Type="Normal" Path="Font/CornDog.ttf" Plist="" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="m_check_box3" ActionTag="910004205" Tag="27" IconVisible="False" LeftMargin="105.9700" RightMargin="33.0300" TopMargin="-3.9981" BottomMargin="1.9981" TouchEnable="True" ctype="CheckBoxObjectData">
                        <Size X="41.0000" Y="42.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="126.4700" Y="22.9981" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.7026" Y="0.5750" />
                        <PreSize X="0.2278" Y="1.0500" />
                        <NormalBackFileData Type="Normal" Path="RoomScene/checkbox_upSkin.png" Plist="" />
                        <PressedBackFileData Type="Normal" Path="RoomScene/checkbox_selectedSkin.png" Plist="" />
                        <NodeNormalFileData Type="Normal" Path="RoomScene/checkbox_selectedSkin.png" Plist="" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint />
                    <Position Y="70.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition Y="0.3500" />
                    <PreSize X="1.0000" Y="0.2000" />
                    <SingleColor A="255" R="150" G="200" B="255" />
                    <FirstColor A="255" R="150" G="200" B="255" />
                    <EndColor A="255" R="255" G="255" B="255" />
                    <ColorVector ScaleY="1.0000" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="80.3715" Y="354.6060" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.1005" Y="0.5910" />
                <PreSize X="0.2250" Y="0.3333" />
                <SingleColor A="255" R="150" G="150" B="255" />
                <FirstColor A="255" R="150" G="150" B="255" />
                <EndColor A="255" R="255" G="255" B="255" />
                <ColorVector ScaleY="1.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="m_thumbnail" ActionTag="813117532" Tag="27" IconVisible="False" LeftMargin="296.8280" RightMargin="352.1720" TopMargin="34.8987" BottomMargin="434.1013" LeftEage="15" RightEage="15" TopEage="15" BottomEage="15" Scale9OriginX="15" Scale9OriginY="15" Scale9Width="121" Scale9Height="101" ctype="ImageViewObjectData">
                <Size X="151.0000" Y="131.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="372.3280" Y="499.6013" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.4654" Y="0.8327" />
                <PreSize X="0.1887" Y="0.2183" />
                <FileData Type="Normal" Path="RoomScene/blank.png" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="r_list_view" ActionTag="768128021" Tag="18" IconVisible="False" LeftMargin="77.7047" RightMargin="542.2953" TopMargin="332.0248" BottomMargin="67.9752" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ScrollDirectionType="0" DirectionType="Vertical" ctype="ListViewObjectData">
                <Size X="180.0000" Y="200.0000" />
                <Children>
                  <AbstractNodeData Name="role_item1" ActionTag="-1621213319" Tag="19" IconVisible="False" BottomMargin="160.0000" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                    <Size X="180.0000" Y="40.0000" />
                    <Children>
                      <AbstractNodeData Name="r_text1" ActionTag="-1770182394" Tag="20" IconVisible="False" LeftMargin="15.5220" RightMargin="106.4780" TopMargin="7.7140" BottomMargin="10.2860" FontSize="20" LabelText="Bazzi" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="58.0000" Y="22.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="44.5220" Y="21.2860" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="0" />
                        <PrePosition X="0.2473" Y="0.5321" />
                        <PreSize X="0.3222" Y="0.5500" />
                        <FontResource Type="Normal" Path="Font/CornDog.ttf" Plist="" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="r_check_box1" ActionTag="-979257676" Tag="21" IconVisible="False" LeftMargin="105.9700" RightMargin="33.0300" TopMargin="-3.9981" BottomMargin="1.9981" TouchEnable="True" ctype="CheckBoxObjectData">
                        <Size X="41.0000" Y="42.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="126.4700" Y="22.9981" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.7026" Y="0.5750" />
                        <PreSize X="0.2278" Y="1.0500" />
                        <NormalBackFileData Type="Normal" Path="RoomScene/checkbox_upSkin.png" Plist="" />
                        <PressedBackFileData Type="Normal" Path="RoomScene/checkbox_selectedSkin.png" Plist="" />
                        <NodeNormalFileData Type="Normal" Path="RoomScene/checkbox_selectedSkin.png" Plist="" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint />
                    <Position Y="160.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition Y="0.8000" />
                    <PreSize X="1.0000" Y="0.2000" />
                    <SingleColor A="255" R="150" G="200" B="255" />
                    <FirstColor A="255" R="150" G="200" B="255" />
                    <EndColor A="255" R="255" G="255" B="255" />
                    <ColorVector ScaleY="1.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="role_item2" ActionTag="-730911829" ZOrder="1" Tag="22" IconVisible="False" TopMargin="40.0000" BottomMargin="120.0000" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                    <Size X="180.0000" Y="40.0000" />
                    <Children>
                      <AbstractNodeData Name="r_text2" ActionTag="1407405009" Tag="23" IconVisible="False" LeftMargin="14.0220" RightMargin="104.9780" TopMargin="7.7140" BottomMargin="10.2860" FontSize="20" LabelText="Cappi" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="61.0000" Y="22.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="44.5220" Y="21.2860" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="0" />
                        <PrePosition X="0.2473" Y="0.5321" />
                        <PreSize X="0.3389" Y="0.5500" />
                        <FontResource Type="Normal" Path="Font/CornDog.ttf" Plist="" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="r_check_box2" ActionTag="1143551223" Tag="24" IconVisible="False" LeftMargin="105.9700" RightMargin="33.0300" TopMargin="-3.9981" BottomMargin="1.9981" TouchEnable="True" ctype="CheckBoxObjectData">
                        <Size X="41.0000" Y="42.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="126.4700" Y="22.9981" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.7026" Y="0.5750" />
                        <PreSize X="0.2278" Y="1.0500" />
                        <NormalBackFileData Type="Normal" Path="RoomScene/checkbox_upSkin.png" Plist="" />
                        <PressedBackFileData Type="Normal" Path="RoomScene/checkbox_selectedSkin.png" Plist="" />
                        <NodeNormalFileData Type="Normal" Path="RoomScene/checkbox_selectedSkin.png" Plist="" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint />
                    <Position Y="120.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition Y="0.6000" />
                    <PreSize X="1.0000" Y="0.2000" />
                    <SingleColor A="255" R="150" G="200" B="255" />
                    <FirstColor A="255" R="150" G="200" B="255" />
                    <EndColor A="255" R="255" G="255" B="255" />
                    <ColorVector ScaleY="1.0000" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="77.7047" Y="67.9752" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.0971" Y="0.1133" />
                <PreSize X="0.2250" Y="0.3333" />
                <SingleColor A="255" R="150" G="150" B="255" />
                <FirstColor A="255" R="150" G="150" B="255" />
                <EndColor A="255" R="255" G="255" B="255" />
                <ColorVector ScaleY="1.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="r_thumbnail" ActionTag="-737473764" Tag="25" IconVisible="False" LeftMargin="295.7677" RightMargin="353.2323" TopMargin="417.7877" BottomMargin="51.2123" LeftEage="15" RightEage="15" TopEage="15" BottomEage="15" Scale9OriginX="15" Scale9OriginY="15" Scale9Width="121" Scale9Height="101" ctype="ImageViewObjectData">
                <Size X="151.0000" Y="131.0000" />
                <AnchorPoint />
                <Position X="295.7677" Y="51.2123" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="159" G="191" B="250" />
                <PrePosition X="0.3697" Y="0.0854" />
                <PreSize X="0.1887" Y="0.2183" />
                <FileData Type="Normal" Path="RoomScene/blank.png" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="0.0001" Y="-1.2775" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition Y="-0.0021" />
            <PreSize X="1.0000" Y="1.0000" />
            <FileData Type="Normal" Path="RoomScene/background1.png" Plist="" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>